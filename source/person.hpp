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
	static sp_Person createPerson(const string& given_name)
	{
		sp_Person person = std::make_shared<Person>(given_name);
		person->me_ = person;
		return person;
	};
	Person();
	Person(const string& given_name); // constructor
	// operator= and copy c-tor make no sense here
	virtual ~Person(); // destructor -> calls all portfolio movies to act accordingly
	virtual void quitMovie(wp_Movie movie); // resign from acting in a movie (calls a particular movie to execute correct methods)
	string getName() const { return name; }; // name getter
	wp_MovieSet getPortfolio() const { return portfolio; }; // portfolio getter
	virtual void movieAdd(wp_Movie movie); // add "movie" to the portfolio !!! this should only be called by Movie::employ()
	//friend std::ostream& operator<<(std::ostream& os, const Character& character); // return name as ostream&
protected:
	string name;
	wp_MovieSet portfolio;
private:	
	wp_Person me_;
};

//#include "movie.hpp" // ????

#endif // !person_hpp