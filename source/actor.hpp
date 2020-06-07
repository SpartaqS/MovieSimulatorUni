/* Actor:
	Can play one or more Characters
	Can work on many movies
*/
#ifndef actor_hpp
#define actor_hpp

#include "person.hpp"

class Actor;
using sp_Actor = std::shared_ptr<Actor>;
using sp_ActorsList = std::list<sp_Actor>;
using wp_Actor = std::weak_ptr<Actor>;
using wp_ActorsSet = std::set<wp_Actor>;

class Actor : public Person
{
public:
	static sp_Actor createActor(const string& given_name)
	{
		sp_Actor actor = std::make_shared<Actor>(given_name);
		actor->me_ = actor;
		return actor;
	};
	Actor(const string &given_name); // constructor
	//virtual void quitMovie(const string& movie_name);
	virtual void quitMovie(wp_Movie movie); // resign from acting in a movie
	virtual void movieAdd(wp_Movie movie);
	//virtual ~Actor(); // destructor -> calls all portfolio movies to act accordingly
private:
	wp_Actor me_;
};

#endif // !actor_hpp