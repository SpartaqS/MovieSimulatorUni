/* Movie:
	Consists of Scenes, Characters , and team (Actors and Directors)
	The owner od Scenes and Characters
	Manages scenes, can be played (streams all scenes in chronological order)
*/
#ifndef movie_hpp
#define movie_hpp

#include <exception>
#include "scene.hpp"

class Movie : std::enable_shared_from_this<Movie>
{
public:
	Movie(const string& m_title, const string& m_genre); //constructor
	// operator= and copy c-tor make no sense here
	~Movie(); //destructor
	/* Actor/Director adding/removing */
	void employ(sp_Person person); // add an person to team (actors: allow them to play characters, directors : allow them directing scenes), if person already in team : throw exception
	void fire(sp_Person person); // remove the person from the team, call critical methods to handle this situation, if person nonexistent in team : throw exception
	/* Actor Management */
	void actorRoleSwap(const sp_Actor actor1, const sp_Actor actor2); // swap all occurences of actor1 and actor2 in characters (list)
	/* Character Management */
	void characterCreate(const string &c_name, const string &c_descr);// overloaded method "sceneCreate" for adding new Character
	//sceneCreate a new character, if there exists a character with name == c_name : force setName the new character
	void remove(sp_Character character); // delete a character, if they are present in at least one scene, create a placeholder character to keep all scenes in tact
	sp_Character character(const string& c_name); // get shared pointer to a Character, if there is no character with name == c_name : throw exception
	/* Scene Management */ // <-- those could be overloaded to use scene numbers too but not sure if that's needed 
	void sceneCreate(const string& s_name, const string& s_desc, sp_Director director, sp_CharactersVector& s_characters);  // sceneCreate a new scene at the end of the scenario, if there exists a scene with the same name: force rename the new scene
	void sceneCreate(const string& s_name, const string& s_desc, sp_Director director);  // sceneCreate a new scene at the end of the scenario, if there exists a scene with the same name: force rename the new scene
	void sceneDelete(sp_Scene scene); // delete a scene from the scenario, Movie::scene() ensures the correctness of provided sp_Scene 
	void sceneSwap(sp_Scene s1, sp_Scene s2); // swap order of scenes s1 and s2, their validity is checked by selecting them using Movie::scene()
	//maybye add scene swap by numbers
	sp_Scene scene(const string& s_name); //get shared pointer to a Scene, if there is no scene with name == s_name : throw exception
	sp_Scene scene(const unsigned int s_number); //get shared pointer to a Scene, if s_number out of range : throw exception

	ostream& credits(ostream& os); // play just credits, format: (character1 - actor1, actor2 ...)
	ostream& play(ostream& os); //play the whole movie (return as stream)

	string getTitle() const { return title; }; // title getter
	void setTitle(const string& m_new_title); // title setter
	string getGenre() const { return genre; }; // genre getter
	void setGenre(const string& m_new_genre); // genre setter
	sp_ScenesList getScenario() { return scenario; }; //scenario (scene list) getter
	sp_CharactersList getCharacters() { return characters; }; // characters getter
	sp_PersonsSet getCast() { return team; }; // team (person list) getter
private:
	string title;
	string genre;
	sp_ScenesList scenario;
	sp_CharactersList characters;
	sp_PersonsSet team;
	bool isDuplicateCharacterByName(string c_name, unsigned int copy_num);
	bool isDuplicateSceneByName(string s_name, unsigned int copy_num);
	bool isCharacterInScenario(const string& c_name);
	bool isInTeam(sp_Person person);
	personType recognizePersonRole(sp_Person person); //check if this person is an Actor, Director or just base Person
};


using string = std::string;
//using sp_Movie = std::shared_ptr<Movie>;
//using sp_MovieList = std::list<sp_Movie>;

#endif // !movie_hpp