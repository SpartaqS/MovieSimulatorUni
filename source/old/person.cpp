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

void Person::quitMovie(const string& m_name)
{
	for (sp_Movie movie : portfolio)
		if (movie->getTitle() == m_name) // movie is removed from portfolio via removeMovie(), called by the movie that is being removed
		{
			movie->fire(std::make_shared<Person>(*this)); //!ISSUE here I need to pass a shared pointer to the person that is calling the method, so Movie can compare it with its own pointer to this Person (and do stuff from Movie::fire() )
		} //!ISSUE again, the new pointer immiedately dies after leaving this method (Person::quitMovie() ), so we have problems.
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
