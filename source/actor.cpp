/* Actor declaration
*/
#include "actor.hpp"
#include "movie.hpp"

Actor::Actor(const string& given_name) : Person(given_name) {}
/*
void Actor::quitMovie(const string& movie_name)
{
	for (sp_Movie sel_movie : portfolio)
		if (sel_movie.lock()->getTitle() == movie_name)
			quitMovie(sel_movie);
}*/

void Actor::quitMovie(sp_Movie movie)
{
	if (movie->isWorkingForThisMovie(me_.lock())) //if not: do nothing
	{
		for (sp_Character sel_character : movie->getCharacters())
			sel_character->actorRemove(me_.lock());
		movie->getCast().erase(me_.lock());
		portfolio.erase(movie);
	}
}

void Actor::movieAdd(sp_Movie movie)
{
	portfolio.insert(movie);
	movie->getCast().insert(me_.lock());
}

/*Actor::~Actor()
{
	//nonexistent because Base Destructor takes care of everything
}*/