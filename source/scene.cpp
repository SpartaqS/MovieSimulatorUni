/*
	Scene:
	methods and functions implementation
*/

#include "scene.hpp"
#include <iostream> // error output

Scene::Scene(const string& s_name, const string& s_desc, sp_Director director, sp_CharactersVector& characters) : name(s_name), description(s_desc), scene_characters(characters)
{
	if ( charactersInDescription() != scene_characters.size() ) // handling incorrect number of "%s" and characters in pass_characters
		throw std::exception("Number of characters in scene.description is different than number of given character pointers.");
	directorAdd(director);
}

Scene::Scene(const string& s_name, const string& s_desc, sp_Director director) : name(s_name), description(s_desc)
{
	directorAdd(director);
}

/*Scene::Scene(const Scene& scene) : name(scene.name), description(scene.description), scene_characters(scene.scene_characters), scene_directors(scene.scene_directors) {}

Scene& Scene::operator=(const Scene& scene)
{
	name = scene.name;
	description = scene.description;
	scene_characters = scene.scene_characters;
	scene_directors = scene.scene_directors;
	return *this;
}*/

Scene::~Scene()
{
	// I guess this is empty because smart pointers can manage themselves
}

ostream& operator<<(ostream& os, const Scene& sc)
{
	if (sc.scene_directors.size() > 0)
	{
		string str = sc.description; //copy description
		for (int i = 0, strIter = str.find("%c"); strIter != string::npos; strIter = str.find("%c"), i++) // replace all "%c" with names of characters 
		{
			str.replace(strIter, 2, sc.scene_characters[i]->getName());
		}
		os << str << "\n";
	}
	return os;
}

void Scene::replace(sp_Character toReplace, sp_Character withWhom)
{
	for (unsigned int i = 0; i < scene_characters.size(); i++)
	{
		if (scene_characters[i] == toReplace)
			scene_characters[i] = withWhom;
	}
}

void Scene::replace(unsigned int number, sp_Character withWhom)
{
	if (number < scene_characters.size()) //number is an unsigned int so it cannot be smaller than 0 (no need to check that)
		scene_characters[number] = withWhom;
	//else
		//std::cerr << "Action::replace(unsigned int number, shared_ptr<character> withWhom) : provided number out of range, doing nothing\n";
		//throw std::invalid_argument("Action::replace(unsigned int number, shared_ptr<character> withWhom) : provided number out of range, doing nothing");
}

void Scene::directorAdd(sp_Director director)
{
	scene_directors.push_back(director);
}

void Scene::directorRemove(sp_Director s_director)
{
	scene_directors.remove(s_director);
}

size_t Scene::charactersInDescription()
{
	size_t foundCount = 0;
	string::size_type pos = 0;
	while ((pos = description.find("%c", pos)) != string::npos) {
		++foundCount;
		pos += 2;
	}
	return foundCount;
}