/* Actor declaration
*/

#include "actor.hpp"


Actor::Actor(const string& given_name)
{
	name = given_name;
}

/*Actor::Actor(const Actor& actor)
{
	name = actor.name;
	portfolio = actor.portfolio;
} */

/*Actor::~Actor()
{
	//empty because Base Destructor takes care of everything
}*/