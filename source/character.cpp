#include "character.hpp"

Character::Character(const string & c_name, const string & c_descr) : name(c_name) , description(c_descr) {}

Character::Character(const Character & character) : name(character.name) , description(character.description) {}
