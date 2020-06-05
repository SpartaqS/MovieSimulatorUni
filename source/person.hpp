/* Person:
	A basic human, base class for Actor and Director
*/
#ifndef person_hpp
#define person_hpp

#include <string>
#include <list>
#include <vector>
#include <set>
#include <memory>

#include <exception>
//#include "movie.hpp"

class Movie;
using wp_Movie = std::weak_ptr<Movie>;
using wp_MovieSet = std::set<wp_Movie>;
using sp_Movie = std::shared_ptr<Movie>;

class Person; //predefinition
using wp_Person = std::weak_ptr<Person>;
using sp_Person = std::shared_ptr<Person>;
using wp_PersonsSet = std::set<wp_Person>;

using string = std::string;

class Person // actual definition
{
public:
	Person();
	Person(const string& given_name); // constructor
	// operator= and copy c-tor make no sense here
	virtual ~Person(); // destructor -> calls all portfolio movies to act accordingly
	void quitMovie(const string& movie_name); // resign from acting in a movie with "movie_name" title. If no movie with this name: do nothing
	void quitMovie(wp_Movie movie); // resign from acting in a movie (calls a particular movie to execute correct methods)
	string getName() const { return name; }; // name getter
	wp_MovieSet getPortfolio() const { return portfolio; }; // portfolio getter
	void movieAdd(wp_Movie movie); // add "movie" to the portfolio !!! this should only be called by Movie::employ()
	void movieRemove(wp_Movie movie); //remove "movie" from portfolio : !!! this should only be called by Movie::fire()
	//friend std::ostream& operator<<(std::ostream& os, const Character& character); // return name as ostream&
private:
	string name;
	wp_MovieSet portfolio;
	void joinAllMovies();
	wp_Person me_;
public:
};

//#include "movie.hpp" // ????

#endif // !person_hpp