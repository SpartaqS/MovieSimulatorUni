/* Actor declaration
*/

#include "actor.hpp"


Actor::Actor(const string& given_name)
{
	name = given_name;
}

Actor::Actor(const Actor& actor)
{
	name = actor.name;
	portfolio = actor.portfolio;
	// employ this into all movies that person is working on
	wp_MovieList::iterator MovieListIter;
	/*for (MovieListIter = portfolio.begin(); MovieListIter != portfolio.end(); MovieListIter++)
	{
		MovieListIter->lock()->employ(std::make_shared<Actor>(*this));
	}*/
}

/*Actor::~Actor()
{
	//empty because Base Destructor takes care of everything
}*/