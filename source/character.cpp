#include "character.hpp"

Character::Character(const string & c_name, const string & c_descr) : name(c_name) , description(c_descr) {}

Character::~Character()
{
	// I guess this is empty because smart pointers can manage themselves
}

void Character::setName(const string & new_c_name)
{
	name = new_c_name;
}

void Character::setDescription(const string & new_c_descr)
{
	description = new_c_descr;
}

void Character::actorAdd(const sp_Actor new_c_actor)
{
	for (sp_Actor selected : actors) // checking if we are adding a new actor to the list
	{
		if (selected == new_c_actor)
			throw std::runtime_error("Exception: Character::addActor : cannot add an Actor twice to a character");
	}
	// new_c_actor not found in list, adding
	actors.push_back(new_c_actor);
}

void Character::actorReplace(const sp_Actor old_c_actor, const sp_Actor new_c_actor)
{
	for (sp_Actor selected : actors)
	{
		if (selected == old_c_actor)
		{
			selected = new_c_actor;
			break; // because any actor can be in the list only once, we can end our search when we replaced the first occurence
		}
	}
}

void Character::actorRemove(const sp_Actor c_actor)
{
	actors.remove(c_actor);
}
