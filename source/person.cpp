#include <iostream>

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
	movie.lock()->getMisc().erase(me_.lock());
	portfolio.erase(movie.lock());
}

void Person::movieAdd(wp_Movie movie)
{
	std::cout << "added by person\n";
	portfolio.insert(movie.lock());
	movie.lock()->getMisc().insert(me_.lock());
}
