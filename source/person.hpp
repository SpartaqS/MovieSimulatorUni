/* Person:
	A basic human, base class for Actor and Director
*/
#ifndef person_hpp
#define person_hpp

#include <string>
#include <list>
#include <vector>
#include <set>

#include <exception>
//#include "movie.hpp"

class Movie;
using sp_Movie = std::shared_ptr<Movie>;
using sp_MovieList = std::list<sp_Movie>;

using string = std::string;

class Person
{
public:
	Person();
	Person(const string& given_name); // constructor
	Person(const Person& person); // copy constructor
	Person& operator=(const Person& person); //assignment operator
	virtual ~Person(); // destructor -> calls all portfolio movies to act accordingly
	void quitMovie(string m_name); // resign from acting in a movie (calls a particular movie to execute correct methods)
	string getName() const { return name; }; // name getter
	sp_MovieList getPortfolio() const { return portfolio; }; // portfolio getter
	//friend std::ostream& operator<<(std::ostream& os, const Character& character); // return name as ostream&
protected:
	string name;
	sp_MovieList portfolio;
	void joinAllMovies();
};

using sp_Person = std::shared_ptr<Person>;
using sp_PersonsSet = std::set<sp_Person>;
using wp_Person = std::weak_ptr<Person>;
//using wp_PersonsSet = std::set<wp_Person>;

//#include "movie.hpp" // ????

#endif // !person_hpp