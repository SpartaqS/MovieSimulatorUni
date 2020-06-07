/* Actor declaration
*/
#include <iostream>

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
	movie->getCast().erase(me_.lock());
	portfolio.erase(movie);
}

void Actor::movieAdd(sp_Movie movie)
{
	std::cout << "added by actor\n";
	portfolio.insert(movie);
	sp_Actor temp = me_.lock();
	movie->getCast().insert(temp);
	std::cout << "size now :" << movie->getCast().size() << "\n";
	int x = 1;
}

/*Actor::~Actor()
{
	//nonexistent because Base Destructor takes care of everything
}*/