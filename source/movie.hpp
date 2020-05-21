/* Movie:
	Consists of Scenes, Characters , and team (Actors and Directors)
	The owner od Scenes and Characters
	Manages scenes, can be played (streams all scenes in chronological order)
*/
#ifndef movie_hpp
#define movie_hpp

using string = std::string;
using sp_Movie = std::shared_ptr<Movie>;
using wp_MovieList = std::list<sp_Movie>;

#include "scene.hpp"

class Movie
{
public:
	Movie(const string& m_title, const string& m_genre); //constructor
	Movie(const Movie& movie); // copy constructor
	Movie& operator= (const Movie& movie); // assignment operator
	~Movie(); //destructor
	/* Actor/Director adding/removing */
	void employ(sp_Person person); // THIS!!!!!  // add an person to team (actors: allow them to play characters, directors : allow them directing scenes), if person already in team : throw exception
	void fire(sp_Person person); // remove the person from the team, call critical methods to handle this situation, if person nonexistent in team : throw exception
	/* Actor Management */
	void actorRoleSwap(const sp_Actor actor1, const sp_Actor actor2); // swap all occurences of actor1 and actor2 in characters (list)
	/* Character Management */
	void createCharacter(const string& c_name,const string& c_description); // a more specific method, basically taking arguments of a constructor
	void create(const Character& character); // overloaded method "create" for adding new Character
	//create a new character, if there exists a character with name == c_name : force rename the new character
	void characterDelete(const string& c_name); // delete a character, if there is no character with name == c_name : throw exception
	sp_Character character(const string& c_name); // get shared pointer to a Character, if there is no character with name == c_name : throw exception
	/* Scene Management */ // <-- those could be overloaded to use scene numbers too but not sure if that's needed 
	void create(const Scene& scene); // create a new scene at the end of the scenario, if there exists a scene with the same name: force rename the new scene
	void sceneDelete(const string& s_name); // delete a scene from the scenario, if there is no scene with name == s_name : throw exception
	void sceneDelete(const unsigned int& number ); //delete number-th scene from the scenario, if out of range : throw exception
	void sceneSwap(const string& s1_name, const string& s2_name); // swap order of scenes s1 and s2, if at least one s_name is invalid : throw exception
	//maybye add scene swap by numbers
	sp_Scene scene(const string& s_name); //get shared pointer to a Scene, if there is no scene with name == s_name : throw exception
	
	string credits(); // play just credits, format: (character1 - actor1, actor2 ...)
	friend ostream& operator<<(ostream& os, const Movie& m); //play the whole movie (return as stream)

	string getTitle() const { return title; }; // title getter
	void setTitle(const string& m_new_title); // title setter
	string getGenre() const { return genre; }; // genre getter
	void setGenre(const string& m_new_genre); // genre setter
	sp_ScenesList getScenario() { return scenario; }; //scenario (scene list) getter
	sp_CharactersVector getCharacters() { return characters; }; // characters getter
	sp_PersonsSet getCast() { return team; }; // team (person list) getter
private:
	string title;
	string genre;
	sp_ScenesList scenario;
	sp_CharactersVector characters;
	sp_PersonsSet team;
};
#endif // !movie_hpp