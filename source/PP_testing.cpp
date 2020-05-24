/* Preliminary Project : Testing
	Gabriel Skowron-Rodriguez */

#include <iostream>
#include "movie.hpp"

int main()
{
	//////* Creating a basic Movie and modifying its title and genre */
	Movie movie1("The Ordinary Movie", "Romantic Thriller");
	if (movie1.getTitle() != "The Ordinary Movie")
		std::cout << "movie title getter error!\n";
	if (movie1.getGenre() != "Romantic Thriller")
		std::cout << "movie genre getter error!\n";
	movie1.setTitle("Super Original Movie");
	if (movie1.getTitle() != "Super Original Movie")
		std::cout << "movie title setter error!\n";
	movie1.setGenre("Fantasy Opera");
	if (movie1.getGenre() != "Fantasy Opera")
		std::cout << "movie genre setter error!\n";

	//////* Creating Actors and employing/firing them to work on a movie */

	std::shared_ptr<Actor> actor1 = std::make_shared<Actor>("Adam Actual");
	std::shared_ptr<Actor> actor2 = std::make_shared<Actor>("Bernard Baker");
	std::shared_ptr<Actor> actor3 = std::make_shared<Actor>("Carol Ceasfire");


	movie1.employ(actor1); // correct: employing actors to movie1
	movie1.employ(actor2);
	if (movie1.getCast().size() != 2)
		std::cout << "actor employment error (Movie::actorEmploy())";

	movie1.employ(actor2); // trying to employ an actor who already works on movie1
	if (movie1.getCast().size() != 2)
		std::cout << "duplicate actor employment error (Movie::actorEmploy())";

	movie1.fire(actor1); // correct: trying to remove an actor that does works on a movie1
	if (movie1.getCast().size() != 1)
		std::cout << "actor fire error (Movie::actorFire())\n";
	
	movie1.fire(actor1); // incorrect: trying to remove an actor that does not work on a movie1
	if (movie1.getCast().size() != 1)
		std::cout << "nonexistent actor fire error (Movie::actorFire())";

	movie1.employ(actor1); // add the actor back for further testing

//////* Creating Directors and employing them */

	std::shared_ptr<Director> director1 = std::make_shared<Director>("Zedaph Zebra");
	movie1.employ(director1);

	//////* Creating Characters and assigning Actors to them */

	movie1.characterCreate("Bobby", "A blonde, well built man always dressed in a red shirt and green trousers");
	movie1.characterCreate("Stephen", "Auburn haired, fit man. Likes to wear a blue jacket and purple pants");
	movie1.characterCreate("Teddy", "Auburn haired, fit man. Stephen's younger twin. Likes to wear a purple jacket and blue pants");

	movie1.character("Bobby")->addActor(actor1); // correct : adding actors to a character (assigning them a role)
	movie1.character("Bobby")->addActor(actor2);
	movie1.character("Bobby")->addActor(actor3);
	try{ 
		movie1.character("Bobby")->addActor(actor3);
		std::cout << "missing exception in Character::addActor()\n";
	}
	catch(std::exception& e) {}

	if (movie1.character("Bobby")->getActorsCount() != 3)
		std::cout << "error adding an actor to a character\n";
	movie1.character("Bobby")->removeActor(actor1); // correct : removing an actor from a character
	if (movie1.character("Bobby")->getActorsCount() != 2)
		std::cout << "error removing an actor from a character\n";

	movie1.character("Stephen")->addActor(actor1);


	movie1.actorRoleSwap(actor1, actor3); // correct: all roles of actor1 and actor2 are swapped
	movie1.character("Stephen")->replaceActor(actor3, actor1); // correct: replaces actor3 with actor1 as character "Stephen"

//////* Creating and modifying Scenes */

	sp_CharactersVector SC1Characters = { movie1.character("Stephen"), movie1.character("Bobby") };

	movie1.sceneCreate("SC1Park", "%c and %c are entering the park", director1, SC1Characters); // correct : create a scene

	if (movie1.getScenario().size() != 1)
		std::cout << "Error creating a scene\n";
	
	if (movie1.scene("SC1Park")->getName() != "SC1Park")
		std::cout << "Scene::getName() error\n";
	if (movie1.scene("SC1Park")->getDescription() != "%c and %c are entering the park")
		std::cout << "Scene::gerDescription() error\n";

	movie1.scene("SC1Park")->setName("SC1Park1"); // correct : rename a scene
	
	try {
		// incorrect : trying to access a scene which does not exist
		movie1.scene("SC1Park");
		std::cout << "missing exception in Movie::scene() when trying to access nonexistent scene\n";
	}
	catch (std::exception& e) {}
	
	if (movie1.scene("SC1Park1")->getName() != "SC1Park1")
		std::cout << "Scene::getName() error\n";

	try {
		// incorrect : too many "%c" character markers in action description (exception is thrown)
		movie1.sceneCreate("SC1Park2","Something's wrong? %c asks %c, and %c responds", director1, SC1Characters);
	}
	catch (std::exception& e) {}

	std::cout << "scene1:\n" << *movie1.scene("SC1Park1") << "\n"; /* playing scene1, scene can be played because there is a director ,output should be:
	Stephen and Bobby are entering the park
	*/
	try {
		// incorrect : character "Teddy" not in this action (exception is thrown)
		movie1.scene("SC1Park1")->replace(movie1.character("Teddy"), movie1.character("Stephen"));
	}
	catch (std::exception& e) {}
	movie1.scene("SC1Park1")->replace(movie1.character("Stephen"), movie1.character("Teddy")); // correct : replacing character "Stephen" with "Teddy"

	std::cout  << *movie1.scene("SC1Park1") << "\n"; /* playing scene1, output should be:
	Teddy and Bobby are entering the park
	*/
	// creating a more scenes
	movie1.sceneCreate("SC2Street", "The traffic lights have turned green\nCars are moving through the street", director1);
	movie1.sceneCreate("SC3DeletedScene", " Pointless text ", director1);
	movie1.scene("SC3DeletedScene")->directorRemove(director1); // removing a director (for example is fired), now this scene will not be played until at least one director is assigned

	std::cout << "x" << *movie1.scene("SC3DeletedScene") << "x\n"; // correct: the scene will not be printed as there are no directors (the stream is unchanged)

//////* Managing scenes */

	movie1.play(std::cout) << "\n"; /* plays the whole movie, as of now there are only 2 scenes so the output is:
	Teddy and Bobby are entering the park
	The traffic lights have turned green
	Cars are moving through the street
	*/
	movie1.sceneSwap("SC1Park1", "SC2Street"); // correct : swapping positions of two scenes
	movie1.play(std::cout) << "\n"; /* now the output of playing a movie is:
	The traffic lights have turned green
	Cars are moving through the street
	Teddy and Bobby are entering the park
	*/
	movie1.sceneDelete("SC3DeletedScene"); // correct : deleting a scene

//////* Actors resigning and credits */
	movie1.credits(std::cout); /*plays credits
	  Directed by:
	Zedaph Zebra

	  Roles:
	Bobby - Bernard Baker, stunt: Carol Ceasfire
	Stephen - Adam Actual
	Teddy - *Computer Generated*
	*/
	actor3->quitMovie("Super Original Movie"); // correct : Carol Ceasfire resigns from working on a movie
	movie1.credits(std::cout) << "\n"; /* now credits do not show Carol Ceasfire...
	  Directed by:
	Zedaph Zebra

	  Roles:
	Bobby - Bernard Baker
	Stephen - Adam Actual
	Teddy - *Computer Generated*
	*/
	std::cout << "Showcase tests ended\n";
	return 0;
}