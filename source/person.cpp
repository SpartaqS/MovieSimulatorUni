#include "person.hpp"
#include "movie.hpp"
#include <iostream> //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Person::Person()
{
	name = "UNNAMED";
}

/*Person::Person(const string& given_name)
{
	name = given_name;
}

Person::Person(const Person& person) : name(person.name), portfolio(person.portfolio)
{
	// employ this into all movies that person is working on
	joinAllMovies();
}

Person& Person::operator=(const Person& person)
{
	name = person.name;
	portfolio = person.portfolio;
	// employ this into all movies that person is working on
	joinAllMovies();
	return *this;
}*/

Person::~Person()
{
	// I guess this is empty because smart pointers can manage themselves
}

void Person::quitMovie(const string& m_name)
{
	for (sp_Movie movie : portfolio)
		if (movie->getTitle() == m_name) // movie is removed from portfolio via removeMovie(), called by the movie that is being removed
		{
			std::cout << "found movie to quit\n";
			movie->fire(std::make_shared<Person>(*this));
		}
}

void Person::movieAdd(sp_Movie movie)
{
	portfolio.insert(movie);
}

void Person::movieRemove(const string& m_name)
{
	for (sp_Movie movie : portfolio)
		if (movie->getTitle() == m_name) // movie is removed from portfolio via removeMovie(), called by the movie that is being removed
		{
			std::cout << "found movie to remove\n";
			portfolio.erase(movie);
			break;
		}
}

void Person::joinAllMovies()
{
	for (sp_Movie selected : portfolio)
	{
		selected->employ(std::make_shared<Person>(*this));
	}
}
