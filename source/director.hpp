/* Director:
	At least one is needed for a Scene to be played.
	Can work on many movies
*/
#ifndef director_hpp
#define director_hpp

#include "person.hpp"

class Director;
using sp_Director = std::shared_ptr<Director>;
using sp_DirectorsList = std::list<sp_Director>;
using wp_Director = std::weak_ptr<Director>;
using wp_DirectorsSet = std::set<wp_Director>;

class Director : public Person
{
public:
	static sp_Director createPerson(const string& given_name)
	{
		sp_Director director = std::make_shared<Director>(given_name);
		director->me_ = director;
		return director;
	};
	Director(const string &given_name); // constructor
	// operator= and copy c-tor make no sense here
	//virtual ~Director(); // destructor -> calls all portfolio movies to act accordingly
private:
	wp_Director me_;
};
#endif // !director_hpp