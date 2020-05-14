/*
	Scene:
	methods and functions implementation
*/

#include "scene.hpp"
#include <iostream> // error output

Scene::Scene(const string &s_name, const string &desc, sp_Director director, sp_CharactersVector & characters) : name(s_name), description(desc) 
{
	if (charactersInDescription() != scene_characters.size()) // handling incorrect number of "%s" and characters in pass_characters
	{
		std::cerr << "Number of characters in scene.description is different than number of given character pointers. Aborting";
		exit(1);
	}
}

ostream& operator<<(ostream& os,const Scene& sc)
{
	string str = sc.description; //copy description
	for (int i = 0, strIter = str.find("%c"); strIter != string::npos; strIter = str.find("%c"), i++) // replace all "%c" with names of characters 
	{
		str.replace(strIter, 2, sc.scene_characters[i]->getName());
	}
	os << str << " size: " << str.size() << "\n";
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