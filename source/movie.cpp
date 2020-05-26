#include "movie.hpp"

#include <iostream> //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Movie::Movie(const string & m_title, const string & m_genre) : title(m_title), genre(m_genre) {}

Movie::~Movie()
{
	// I guess this is empty because smart pointers can manage themselves
}

void Movie::employ(sp_Person person)
{
	team.insert(person);
	sp_Movie thisMovie = std::make_shared<Movie>(*this);
	person->movieAdd(thisMovie);
}

void Movie::fire(sp_Person person)
{
	// if actor: cycle through all characters to remove pointers to "person" from them
	if (isInTeam(person)) //if not: do nothing
	{
		if (recognizePersonRole(person) == pt_actor)
		{
			for (sp_Character sel_character : characters)
			{
				std::cout << "removing from character\n";
				sel_character->actorRemove(std::dynamic_pointer_cast<Actor>(person));
			}
		}
		// if director: cycle through all scenes to remove pointers to "person" from them
		else if (recognizePersonRole(person) == pt_director)
		{
			for (sp_Scene sel_scene : scenario)
				sel_scene->directorRemove(std::dynamic_pointer_cast<Director>(person));
		}
		person->movieRemove(title); // asking "person" to remove this movie from their portfolio
		team.erase(person);
	}
}

void Movie::actorRoleSwap(const sp_Actor actor1, const sp_Actor actor2)
{
	for (sp_Character sel_character : characters)
	{
		for (sp_Actor sel_actor : sel_character->getActorsList() )// swap actor1 into actor2  XOR actor2 into actor1
		{
			if (sel_actor == actor1)
				sel_actor = actor2;
			else if (sel_actor == actor2)
				sel_actor = actor1;
		}
	}
}

void Movie::characterCreate(const string &c_name, const string &c_descr)
{
	Character character(Character(c_name, c_descr));
	unsigned int search_tries = 0;
	while (isDuplicateCharacterByName(character.getName(), search_tries))
	{
		++search_tries;
	}
	if (search_tries > 0) // renaming the character if found at least one with the same name
		character.setName(character.getName().append(std::to_string(search_tries)));
	characters.push_back(std::make_shared<Character>(character));
	int x;
}

void Movie::remove(sp_Character character)
{
	if (isCharacterInScenario(character->getName())) //check if the character appears in at least one scene
	{
		unsigned int placeholder_num = 0;
		while (isDuplicateCharacterByName(character->getName(),placeholder_num))
		{
			++placeholder_num;
		}
		string placeholder_name = "_Placeholder_" + std::to_string(placeholder_num);
		character->setName(placeholder_name);
		character->setDescription("Placeholder Character: replace with an actual character");
	}
	else
	{
		characters.remove(character);
	}
}

sp_Character Movie::character(const string & c_name)
{
	for (sp_Character selected : characters)
	{
		if (selected->getName() == c_name)
		{
			return selected;
		}
	}
	// no character found: throw exception
	throw std::exception("Exception: Movie::character(c_name) : no character with specified name in the list of chaarcters");
}

void Movie::sceneCreate(const string& s_name, const string& s_desc, sp_Director director, sp_CharactersVector& s_characters)
{
	Scene scene(s_name, s_desc, director, s_characters);
	unsigned int search_tries = 0;
	while (isDuplicateSceneByName(scene.getName(), search_tries))
	{
		++search_tries;
	}
	if (search_tries > 0) // renaming the character if found at least one with the same name
		scene.setName(scene.getName().append(std::to_string(search_tries)));
	scenario.push_back(std::make_shared<Scene>(scene));
}

void Movie::sceneCreate(const string & s_name, const string & s_desc, sp_Director director)
{
	Scene scene(s_name, s_desc, director);
	unsigned int search_tries = 0;
	while (isDuplicateSceneByName(scene.getName(), search_tries))
	{
		++search_tries;
	}
	if (search_tries > 0) // renaming the character if found at least one with the same name
		scene.setName(scene.getName().append(std::to_string(search_tries)));
	scenario.push_back(std::make_shared<Scene>(scene));
}

void Movie::sceneDelete(sp_Scene scene)
{
	scenario.remove(scene); // destructor handles pointers
}

void Movie::sceneSwap(sp_Scene s1, sp_Scene s2)
{// no need to check their validity as you should access the scenes using Movie:scene(s_name)/(s_number)
	std::swap(*s1, *s2);
}

sp_Scene Movie::scene(const string & s_name)
{
	for (sp_Scene selected : scenario)
	{
		if (selected->getName() == s_name)
		{
			return selected;
		}
	}
	// no scene found: throw exception
	throw std::exception("Exception: Movie::scene(s_name) : no scene with specified name in the list of scenes (scenario)");
}

sp_Scene Movie::scene(const unsigned int s_number)
{
	if (s_number > scenario.size()) //if out of range then throw exception
		throw std::exception("Exception: Movie::scene(s_number) : provided s_number is out of range (there are less scenes than that)");
	else
	{
		unsigned int sel_num = 0;
		for (sp_Scene sel_scene : scenario)
		{
			if (sel_num == s_number) // found scene -> return it
				return sel_scene;
			++sel_num;
		}
	}
}

ostream& Movie::credits(ostream& os) // !!!!!!!!!!!!!!!!!!!
{
	os << "  Directed by:\n"; // printing all directors
	for (sp_Person sel_person : team)
	{
		if (recognizePersonRole(sel_person) == pt_director)
			os << sel_person->getName() <<"\n";
	}
	os << "\n  Roles:\n";
	for (sp_Character sel_character : characters) // printing out all characters with actors playing them
	{
		os << sel_character->getName() << " - ";
		if (sel_character->getActorsList().size() == 0)
		{
			os << "*Computer Generated*";
		} // printing actors
		else 
		{
			unsigned int actor_num = 1;
			for (sp_Actor sel_actor : sel_character->getActorsList())
			{
				if (actor_num == 2) // start listing the one stunt
					if(sel_character->getActorsList().size() == 2)
						os << "stunt: ";
					else // start listing all stunts
						os << "stunts: ";
				os << sel_actor->getName();
				if (actor_num < sel_character->getActorsList().size())
					os << ", ";
				++actor_num;
			}
		}
		os << "\n";
	}
	return os; 
}

void Movie::setTitle(const string & m_new_title)
{
	title = m_new_title;
}

void Movie::setGenre(const string & m_new_genre)
{
	genre = m_new_genre;
}

bool Movie::isDuplicateCharacterByName(string c_name, unsigned int copy_num)
{
	if(copy_num > 0)
		c_name.append(std::to_string(copy_num));

	for (sp_Character selected : characters)
	{
		if (selected->getName() == c_name)
			return true;
	}
	return false;
}

bool Movie::isDuplicateSceneByName(string s_name, unsigned int copy_num)
{
	if (copy_num > 0)
		s_name.append(std::to_string(copy_num));

	for (sp_Scene selected : scenario)
	{
		if (selected->getName() == s_name)
			return true;
	}
	return false;
}

bool Movie::isCharacterInScenario(const string& c_name)
{
	for (sp_Scene selected : scenario)
		for (sp_Character s_character : selected->getSceneCharacters())
			if (s_character->getName() == c_name)
				return true;
	return false;
}

bool Movie::isInTeam(sp_Person person)
{
	for (sp_Person sel_person : team)
		if (sel_person == person)
			return true;
	return false;
}

personType Movie::recognizePersonRole(sp_Person person)
{
	sp_Actor testActor;
	sp_Director testDirector;
	if ((testActor = std::dynamic_pointer_cast<Actor>(person)) != nullptr)
		return pt_actor;
	else if ((testDirector = std::dynamic_pointer_cast<Director>(person)) != nullptr)
		return pt_director;
	return pt_base;
}

ostream& Movie::play(ostream & os)
{
	for (sp_Scene selected : scenario)
	{
		os << *selected;
	}
	return os;
}
