/* Director:
	At least one is needed for a Scene to be played.
	Can work on many movies
*/
#ifndef director_hpp
#define director_hpp

#include "person.hpp"
using wp_Director = std::weak_ptr<Director>;
using wp_DirectorsList = std::list<wp_Director>;
using sp_Director = std::shared_ptr<Director>;

class Director : public Person
{
public:
	Director(const string &given_name); // constructor
	Director(const Director& director); // copy constructor
	Director& operator=(const Director& director); //assignment operator
	virtual ~Director(); // destructor -> calls all portfolio movies to act accordingly
};
#endif // !director_hpp