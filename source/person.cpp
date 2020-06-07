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

void Person::quitMovie(wp_Movie movie)
{
	portfolio.find(movie)->lock()->getMisc().erase(me_);
	portfolio.erase(movie);
}

void Person::movieAdd(wp_Movie movie)
{
	portfolio.insert(movie);
	movie.lock()->getMisc().insert(me_);
}