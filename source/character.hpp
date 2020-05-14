/* Character:
	Exists within a Movie.
	Can be played by multiple actors.
	Used in Scenes to portray movie characters
*/
#ifndef character_hpp
#define character_hpp

#include "actor.hpp"

using sp_Character = std::shared_ptr<Character>;
using sp_CharactersVector = std::vector<sp_Character>;


class Character
{
public:
	Character(const string &given_name); //constructor
	Character(const Character& character); // copy constructor
	Character& operator=(const Character& character); //assignment operator
	~Character(); //destructor -> calls parent movie to handle the problem
	void rename(const string &new_c_name); // change the name of a character, if there is no character with name == c_name : throw exception
	void modifyDescription(const string &new_c_descr); // modify the description of a character, if there is no character wiht name == c_name : throw exception
	void addActor(const sp_Actor new_c_actor); // add a new_c_actor to the end of list of actors, if new_c_actor is already there : throw exception
	void replaceActor(const sp_Actor old_c_actor, const sp_Actor new_c_actor); // replace old_c_actor with new_c_actor
	void removeActor(const sp_Actor c_actor); // remove a c_actor from the list of actors, if there is no c_actor  : throw exception
	string getName() const { return name; }; // name getter
	string getDescription() const { return description; }; // description getter
	wp_ActorsList getActorsList() const { return actors; }; // actors list getter
	size_t getActorsCount() const { return actors.size(); }; // get how many actors play that character
private:
	string name;
	string description;
	wp_ActorsList actors;
};

#endif // !character_hpp