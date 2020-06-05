#include "person.hpp"
#include "movie.hpp"

Person::Person()
{
	name = "UNNAMED";
}

Person::Person(const string& given_name)
{
	name = given_name;
}

Person::~Person()
{
	// I guess this is empty because smart pointers can manage themselves
}

void Person::quitMovie(const string& movie_name)
{
	for (wp_Movie sel_movie : portfolio)
		if (sel_movie.lock()->getTitle() == movie_name)
			sel_movie.lock()->fire(me_);
}

void Person::quitMovie(wp_Movie movie)
{
	portfolio.find(movie)->lock()->fire(me_);
}

void Person::movieAdd(wp_Movie movie)
{
	portfolio.insert(movie);
}

void Person::movieRemove(wp_Movie movie)
{
	portfolio.erase(movie);
}

void Person::joinAllMovies()
{
	for (wp_Movie selected : portfolio)
	{
		selected.lock()->employ(me_);
	}
}
