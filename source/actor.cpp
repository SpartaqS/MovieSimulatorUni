/* Actor declaration
*/

#include "actor.hpp"
#include "movie.hpp"

Actor::Actor(const string& given_name) : Person(given_name) {}

void Actor::quitMovie(const string& movie_name)
{
	for (wp_Movie sel_movie : portfolio)
		if (sel_movie.lock()->getTitle() == movie_name)
			quitMovie(sel_movie);
}

void Actor::quitMovie(wp_Movie movie)
{
	portfolio.find(movie)->lock()->getCast().erase(me_);
	portfolio.erase(movie);
}

void Actor::movieAdd(wp_Movie movie)
{
	portfolio.insert(movie);
	movie.lock()->getMisc().insert(me_);
}

/*Actor::~Actor()
{
	//nonexistent because Base Destructor takes care of everything
}*/