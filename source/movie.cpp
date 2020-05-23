#include "movie.hpp"

Movie::Movie(const string & m_title, const string & m_genre) : title(m_title), genre(m_genre) {}

Movie::Movie(const Movie & movie) : title(movie.title) , genre(movie.genre) {}

Movie & Movie::operator=(const Movie & movie)
{
	// TODO: tu wstawiæ instrukcjê return
	return *this;
}

Movie::~Movie()
{
	// do firing all of team
}

void Movie::employ(sp_Person person)
{
	team.insert(person);
}

void Movie::fire(sp_Person person)
{
	// TO DO cycle through all scenes to remove "person"
	team.erase(person);
}

void Movie::actorRoleSwap(const sp_Actor actor1, const sp_Actor actor2)
{
	// TO DO swap all occurences of actor1 and actor2 in characters (list) actor1->temp, actor2->actor1, temp->actor2
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
}

void Movie::remove(sp_Character character)
{
	if (isCharacterInScenario(character->getName()))
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
	//TO DO clear actors_list, if character found in at least one scene: sceneCreate a placeholder character and cerr: created placeholder character
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

void Movie::sceneDelete(const string & s_name)
{
}

void Movie::sceneDelete(const unsigned int & number)
{
}

void Movie::sceneSwap(const string & s1_name, const string & s2_name)
{
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

string Movie::credits()
{
	// TO DO: Print credits directors,characters:actors (1. at all 2. alphabetically)
	return string();
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

ostream & operator<<(ostream & os, const Movie & m)
{
	// TODO: tu wstawiæ instrukcjê return
	return os;
}
