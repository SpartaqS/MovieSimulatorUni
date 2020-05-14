/* Actor:
	Can play one or more Characters
	Can work on many movies
*/
#ifndef actor_hpp
#define actor_hpp

#include "person.hpp"

using sp_Actor = std::shared_ptr<Actor>;
using wp_ActorsList = std::list<std::weak_ptr<Actor>>;

class Actor : public Person
{
public:
	Actor(const string &given_name); // constructor
	Actor(const Actor& actor); // copy constructor
	Actor& operator=(const Actor& actor); //assignment operator
	virtual ~Actor(); // destructor -> calls all portfolio movies to act accordingly
};
#endif // !actor_hpp