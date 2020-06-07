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

void Person::quitMovie(sp_Movie movie)
{
	movie->getMisc().erase(me_.lock());
	portfolio.erase(movie);
}

void Person::movieAdd(sp_Movie movie)
{
	portfolio.insert(movie);
	movie->getMisc().insert(me_.lock());
}
