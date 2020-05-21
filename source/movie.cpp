#include "movie.hpp"

Movie::Movie(const string & m_title, const string & m_genre) : title(m_title), genre(m_genre) {}

Movie::Movie(const Movie & movie) : title(movie.title) , genre(movie.genre) {}

Movie & Movie::operator=(const Movie & movie)
{
	// TODO: tu wstawiæ instrukcjê return
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

void Movie::create(const Character & character)
{
	// TO DO try to find a character with the same name as new one, if found: rename new character and try to find it again
	characters.push_back(std::make_shared<Character>(character));
}

void Movie::characterDelete(const string & c_name)
{
	//TO DO clear actors_list, if character found in at least one scene: create a placeholder character and cerr: created placeholder character
}

sp_Character Movie::character(const string & c_name)
{
	// TO DO: Find character in characters, if not found: throw exception 
	return sp_Character();
}

void Movie::create(const Scene & scene)
{
	// TO DO try to find a character with the same name as new one, if found: rename new character and try to find it again
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
	// TO DO: like in character()
	return sp_Scene();
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
