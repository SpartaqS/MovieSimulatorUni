/* Character:
	Exists within a Movie.
	Can be played by multiple actors.
	Used in Scenes to portray movie characters
*/
#ifndef character_hpp
#define character_hpp

#include "actor.hpp"

class Character
{
public:
	Character(const string &c_name, const string &c_descr); //constructor
	// operator= and copy c-tor make no sense here
	~Character(); //destructor -> calls parent movie to handle the problem
	void setName(const string &new_c_name); // change the name of a character, if there is no character with name == c_name : throw exception
	void setDescription(const string &new_c_descr); // modify the description of a character, if there is no character wiht name == c_name : throw exception
	void actorAdd(const sp_Actor new_c_actor); // add a new_c_actor to the end of list of actors, if new_c_actor is already there : throw exception
	void actorReplace(const sp_Actor old_c_actor, const sp_Actor new_c_actor); // replace old_c_actor with new_c_actor
	void actorRemove(const sp_Actor c_actor); // remove a c_actor from the list of actors, if there is no c_actor  : do nothing
	string getName() const { return name; }; // name getter
	string getDescription() const { return description; }; // description getter
	sp_ActorsList getActorsList() const { return actors; }; // actors list getter
	size_t getActorsCount() const { return actors.size(); }; // get how many actors play that character
private:
	string name;
	string description;
	sp_ActorsList actors; // no copies of any Actor are allowed (this is not a std::set because order matters)
};

using sp_Character = std::shared_ptr<Character>;
using sp_CharactersList = std::list<sp_Character>;
using sp_CharactersVector = std::vector<sp_Character>;

#endif // !character_hpp