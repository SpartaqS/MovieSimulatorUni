/* Preliminary Project : Testing
	Gabriel Skowron-Rodriguez */

#include <iostream>
#include <sstream> // to test returned "ostream"s
#include "movie.hpp"

int main()
{
	//////* Creating a basic Movie and modifying its title and genre */
	sp_Movie movie1 = Movie::createMovie("The Ordinary Movie", "Romantic Thriller");
	if (movie1->getTitle() != "The Ordinary Movie")
		std::cout << "movie title getter error!\n";
	if (movie1->getGenre() != "Romantic Thriller")
		std::cout << "movie genre getter error!\n";
	movie1->setTitle("Super Original Movie");
	if (movie1->getTitle() != "Super Original Movie")
		std::cout << "movie title setter error!\n";
	movie1->setGenre("Fantasy Opera");
	if (movie1->getGenre() != "Fantasy Opera")
		std::cout << "movie genre setter error!\n";

	//////* Creating Actors and employing/firing them to work on a movie */

	std::shared_ptr<Actor> actor1 = Actor::createActor("Adam Actual");
	std::shared_ptr<Actor> actor2 = Actor::createActor("Bernard Baker");
	std::shared_ptr<Actor> actor3 = Actor::createActor("Carol Ceasfire");


	movie1->employ(actor1); // correct: employing actors to movie1
	movie1->employ(actor2);
	if (movie1->getCast().size() != 2)
		std::cout << "actor employment error (Movie::actorEmploy())\n";

	movie1->employ(actor2); // trying to employ an actor who already works on movie1
	if (movie1->getCast().size() != 2)
		std::cout << "duplicate actor employment error (Movie::actorEmploy())\n";

	movie1->fire(actor1); // correct: trying to remove an actor that does works on a movie1
	if (movie1->getCast().size() != 1)
		std::cout << "actor fire error (Movie::actorFire())\n";
	
	movie1->fire(actor1); // incorrect: trying to remove an actor that does not work on a movie1
	if (movie1->getCast().size() != 1)
		std::cout << "error : (Movie::actorFire())\n";

	movie1->employ(actor1); // add the actor back for further testing
	movie1->employ(actor3);
//////* Creating Directors and employing them */

	std::shared_ptr<Director> director1 = Director::createDirector("Zedaph Zebra");
	movie1->employ(director1);

	//////* Creating Characters and assigning Actors to them */

	movie1->characterCreate("Bobby", "A blonde, well built man always dressed in a red shirt and green trousers");
	if (movie1->getCharacters().size() != 1)
		std::cout << "error adding a a character\n";
	movie1->characterCreate("Stephen", "Auburn haired, fit man. Likes to wear a blue jacket and purple pants");
	if (movie1->getCharacters().size() != 2)
		std::cout << "error adding a a character\n";
	movie1->characterCreate("Teddy", "Auburn haired, fit man. Stephen's younger twin. Likes to wear a purple jacket and blue pants");
	if (movie1->getCharacters().size() != 3)
		std::cout << "error adding a a character\n";

	movie1->character("Bobby")->actorAdd(actor1); // correct : adding actors to a character (assigning them a role)
	movie1->character("Bobby")->actorAdd(actor2);
	movie1->character("Bobby")->actorAdd(actor3);
	try{ 
		movie1->character("Bobby")->actorAdd(actor3);
		std::cout << "missing exception in Character::addActor()\n";
	}
	catch(std::runtime_error&) {}

	if (movie1->character("Bobby")->getActorsCount() != 3)
		std::cout << "error adding an actor to a character\n";
	movie1->character("Bobby")->actorRemove(actor1); // correct : removing an actor from a character
	if (movie1->character("Bobby")->getActorsCount() != 2)
		std::cout << "error removing an actor from a character\n";

	movie1->character("Stephen")->actorAdd(actor1);

	movie1->actorRoleSwap(actor1, actor3); // correct: all roles of actor1 and actor2 are swapped
	movie1->character("Stephen")->actorReplace(actor3, actor1); // correct: replaces actor3 with actor1 as character "Stephen"

	movie1->character("Bobby")->actorAdd(actor1);
	movie1->character("Stephen")->actorAdd(actor3);

//////* Creating and modifying Scenes */
	std::stringstream os; // stringstream used for testing of scenes

	sp_CharactersVector SC1Characters = { movie1->character("Stephen"), movie1->character("Bobby") };

	movie1->sceneCreate("SC1Park", "%c and %c are entering the park", director1, SC1Characters); // correct : create a scene

	if (movie1->getScenario().size() != 1)
		std::cout << "Error creating a scene\n";
	
	if (movie1->scene("SC1Park")->getName() != "SC1Park")
		std::cout << "Scene::getName() error\n";
	if (movie1->scene("SC1Park")->getDescription() != "%c and %c are entering the park")
		std::cout << "Scene::gerDescription() error\n";

	movie1->scene("SC1Park")->setName("SC1Park1"); // correct : rename a scene
	
	try {
		// incorrect : trying to access a scene which does not exist
		movie1->scene("SC1Park");
		std::cout << "missing exception in Movie::scene() when trying to access nonexistent scene\n";
	}
	catch (std::runtime_error&) {}
	
	if (movie1->scene("SC1Park1")->getName() != "SC1Park1")
		std::cout << "Scene::getName() error\n";

	try {
		// incorrect : too many "%c" character markers in action description (exception is thrown)
		movie1->sceneCreate("SC1Park2","Something's wrong? %c asks %c, and %c responds", director1, SC1Characters);
	}
	catch (std::runtime_error&) {}

	if (movie1->getScenario().size() != 1)
		std::cout << "Invalid scene was not deleted\n";

	os << *movie1->scene("SC1Park1"); /* playing scene1, scene can be played because there is a director ,output should be:
	Stephen and Bobby are entering the park
	*/
	if (os.str() != "Stephen and Bobby are entering the park\n")
		std::cout << "Error: operator<< for Scene\n";
	
	try {
		// incorrect : character "Teddy" not in this action (exception is thrown)
		movie1->scene("SC1Park1")->replace(movie1->character("Teddy"), movie1->character("Stephen"));
	}
	catch (std::runtime_error&) {}
	movie1->scene("SC1Park1")->replace(movie1->character("Stephen"), movie1->character("Teddy")); // correct : replacing character "Stephen" with "Teddy"
	os.str(""); // emptying the stream
	os  << *movie1->scene("SC1Park1"); /* playing scene1, output should be:
	Teddy and Bobby are entering the park
	*/
	if (os.str() != "Teddy and Bobby are entering the park\n")
		std::cout << "Error: Scene::replace(sp_Character,sp_Character)\n";

	// creating more scenes
	movie1->sceneCreate("SC2Street", "The traffic lights have turned green\nCars are moving through the street", director1);
	if (movie1->getScenario().size() != 2)
		std::cout << "Error creating multiple scenes (should be 2 scenes now)\n";

	movie1->sceneCreate("SC3DeletedScene", " Pointless text ", director1);
	if (movie1->getScenario().size() != 3)
		std::cout << "Error creating multiple scenes (should be 3 scenes now)\n";

	movie1->scene("SC3DeletedScene")->directorRemove(director1); // removing a director (for example is fired), now this scene will not be played until at least one director is assigned
	if (movie1->getScenario().size() != 3) // removing a director should not remove a scene completely
		std::cout << "Error creating multiple scenes (removing a director should not remove a scene)\n";

	os.str(""); // emptying the stream
	os << *movie1->scene("SC3DeletedScene");// correct: the scene will not be printed as there are no directors (the stream is unchanged)
	if (os.str() != "")
		std::cout << "Error: Scene played without a director\n";

//////* Managing scenes */
	os.str(""); // emptying the stream
	movie1->play(os); /* plays the whole movie to a stream "os", as of now there are only 2 scenes so the output is:
	Teddy and Bobby are entering the park
	The traffic lights have turned green
	Cars are moving through the street
	*/
	if (os.str() != "Teddy and Bobby are entering the park\nThe traffic lights have turned green\nCars are moving through the street\n")
		std::cout << "Error: movie1->play(ostream& os)\n";
	//std::cout << os.str();

	os.str(""); // emptying the stream
	movie1->sceneSwap(movie1->scene("SC1Park1"),movie1->scene("SC2Street")); // correct : swapping positions of two scenes
	movie1->play(os);/* now the output of playing a movie is:
	The traffic lights have turned green
	Cars are moving through the street
	Teddy and Bobby are entering the park
	*/
	if (os.str() != "The traffic lights have turned green\nCars are moving through the street\nTeddy and Bobby are entering the park\n")
		std::cout << "Error: movie1->sceneSwap()\n";
	//std::cout << os.str();

	movie1->sceneDelete(movie1->scene("SC3DeletedScene")); // correct : deleting a scene
	if (movie1->getScenario().size() != 2) // removing a director should not remove a scene completely
		std::cout << "Error: movie1->sceneDelete() has failed\n";


//////* Actors resigning and credits */
	os.str(""); // emptying the stream
	movie1->credits(os); /*plays credits
	  Directed by:
	Zedaph Zebra

	  Roles:
	Bobby - Bernard Baker, stunts: Carol Ceasfire, Adam Actual
	Stephen - Adam Actual, stunt: Carol Ceasfire
	Teddy - *Computer Generated*
	*/
	string credits_test1 = "  Directed by:\nZedaph Zebra\n\n  Roles:\nBobby - Bernard Baker, stunts: Carol Ceasfire, Adam Actual\nStephen - Adam Actual, stunt: Carol Ceasfire\nTeddy - *Computer Generated*\n";
	if (os.str() != credits_test1)
		std::cout << "Error: movie1->credits() 1\n";
	//movie1->fire(actor3);
	actor3->quitMovie(movie1); // correct : Carol Ceasfire resigns from working on a movie
	os.str("");
	movie1->credits(os); /* now credits do not show Carol Ceasfire...
	  Directed by:
	Zedaph Zebra

	  Roles:
	Bobby - Bernard Baker, stunt: Adam Actual
	Stephen - Adam Actual
	Teddy - *Computer Generated*
	*/
	string credits_test2 = "  Directed by:\nZedaph Zebra\n\n  Roles:\nBobby - Bernard Baker, stunt: Adam Actual\nStephen - Adam Actual\nTeddy - *Computer Generated*\n";
	if (os.str() != credits_test2)
		std::cout << "Error: movie1->credits() 2: This one does not work because I do not know how Movie can pass a \"shared_ptr to itself\" as a parameter for Person::movieAdd(sp_Movie)\n";
	std::cout << "Showcase tests ended\n";
	printf("_MSC_VER : %d \n", _MSC_VER);
	printf("_MSC_FULL_VER : %d \n", _MSC_FULL_VER);
	printf("_MSC_BUILD : %d \n", _MSC_BUILD);
	return 0;
}