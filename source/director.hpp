/* Director:
	At least one is needed for a Scene to be played.
	Can work on many movies
*/
#ifndef director_hpp
#define director_hpp

#include "person.hpp"

class Director : public Person
{
public:
	Director(const string &given_name); // constructor
	//Director(const Director& director); // copy constructor
	//Director& operator=(const Director& director); //assignment operator
	//virtual ~Director(); // destructor -> calls all portfolio movies to act accordingly
};
#endif // !director_hpp

using sp_Director = std::shared_ptr<Director>;
using sp_DirectorsList = std::list<sp_Director>;