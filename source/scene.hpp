/* Scene:
	Describes a set of events (using a string)
	Can be played: if there are any "%c" substrings in the description, substitute the %c with a Character's name
*/
#ifndef scene_hpp
#define scene_hpp

#include <ostream>
#include "character.hpp"
#include "director.hpp"

using ostream = std::ostream;

class Scene
{
public:
	Scene(const string &s_name, const string &s_desc, sp_Director director, sp_CharactersVector& s_characters); // constructor (with Characters)
	Scene(const string &s_name, const string &s_desc, sp_Director director); // constructor (without Characters)
	// operator= and copy c-tor make no sense here
	~Scene(); // desctructor
	void replace(sp_Character toReplace, sp_Character withWhom); // changes all appearances of toReplace character into appearances of withWhom character
	void replace(unsigned int number, sp_Character withWhom); // changes number-th character into withWhom character, if number out of range: do nothing
	void directorAdd(sp_Director s_director); // add s_director to scene_directors
	void directorRemove(sp_Director s_director); // remove s_director from scene_directors, if there is no s_director  : do nothing
	friend ostream& operator<<(ostream& os,const Scene& sc); // return scene as one stream
	string getName() const { return name; }; // name getter
	void setName(string new_name) { name = new_name; }; // name setter
	string getDescription() const { return description; }; // raw description getter
	/* description modifying is not planned because methods to actually do so would be too complicated to use and make the code needlessly too long */
	sp_CharactersVector getSceneCharacters() const { return scene_characters; }; // scene_characters getter
private:
	string name;
	string description;
	sp_CharactersVector scene_characters;
	sp_DirectorsList scene_directors;
	size_t charactersInDescription(); // count the number of occurences of special "%c" substring in the description
};

using sp_Scene = std::shared_ptr<Scene>;
using sp_Scenes = std::vector<sp_Scene>;
using sp_ScenesList = std::list<sp_Scene>;

#endif // !scene_hpp
