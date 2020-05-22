#include "character.hpp"

Character::Character(const string & c_name, const string & c_descr) : name(c_name) , description(c_descr) {}

Character::Character(const Character & character) : name(character.name) , description(character.description) {}

Character & Character::operator=(const Character & character)
{
	// TODO: tu wstawiæ instrukcjê return
	return *this;
}

Character::~Character()
{
	// call parent movie to delete the character
}

void Character::rename(const string & new_c_name)
{
	name = new_c_name;
}

void Character::modifyDescription(const string & new_c_descr)
{
	description = new_c_descr;
}

void Character::addActor(const sp_Actor new_c_actor)
{
	for (sp_Actor selected : actors) // checking if we are adding a new actor to the list
	{
		if (selected == new_c_actor)
			throw std::exception("Exception: Character::addActor : cannot add an Actor twice to a character");
	}
	// new_c_actor not found in list, adding
	actors.push_back(new_c_actor);
}

void Character::replaceActor(const sp_Actor old_c_actor, const sp_Actor new_c_actor)
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

void Character::removeActor(const sp_Actor c_actor)
{
	actors.remove(c_actor);
}
