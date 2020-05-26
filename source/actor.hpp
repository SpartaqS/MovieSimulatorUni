/* Actor:
	Can play one or more Characters
	Can work on many movies
*/
#ifndef actor_hpp
#define actor_hpp

#include "person.hpp"

class Actor : public Person
{
public:
	Actor(const string &given_name); // constructor
	//virtual ~Actor(); // destructor -> calls all portfolio movies to act accordingly
};

using sp_Actor = std::shared_ptr<Actor>;
using sp_ActorsList = std::list<sp_Actor>;

#endif // !actor_hpp