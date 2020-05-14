#include "person.hpp"

Person::Person()
{
	name = "UNNAMED";
}

Person::Person(const string& given_name)
{
	name = given_name;
}

Person::Person(const Person& person) : name(person.name), portfolio(person.portfolio)
{
	// employ this into all movies that person is working on
	wp_MovieList::iterator MovieListIter;
	for (MovieListIter = portfolio.begin(); MovieListIter != portfolio.end(); MovieListIter++)
	{
		MovieListIter->lock()->employ(std::make_shared<Person>(*this));
	}
}

Person& Person::operator=(const Person& person)
{
	name = person.name;
	portfolio = person.portfolio;
	// employ this into all movies that person is working on
	wp_MovieList::iterator MovieListIter;
	for (MovieListIter = portfolio.begin(); MovieListIter != portfolio.end(); MovieListIter++)
	{
		MovieListIter->lock()->employ(std::make_shared<Person>(*this));
	}
}

Person::~Person()
{ 
	// "get fired" from all movies
	wp_MovieList::iterator MovieListIter;
	for (MovieListIter = portfolio.begin(); MovieListIter != portfolio.end(); MovieListIter++)
	{
		MovieListIter->lock()->fire(std::make_shared<Person>(*this));
	}
}