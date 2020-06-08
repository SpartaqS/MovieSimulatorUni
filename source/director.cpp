/* Director declaration
*/
#include "director.hpp"
#include "movie.hpp"

Director::Director(const string& given_name) : Person(given_name) {}

/*Director::~Director()
{
	//nonexistent because Base Destructor takes care of everything
}*/

void Director::quitMovie(sp_Movie movie)
{
	if (movie->isWorkingForThisMovie(me_.lock())) //if not: do nothing
	{
		for (sp_Scene sel_scene : movie->getScenario())
			sel_scene->directorRemove(me_.lock());
		movie->getDirectors().erase(me_.lock());
		portfolio.erase(movie);
	}
}

void Director::movieAdd(sp_Movie movie)
{
	portfolio.insert(movie);
	movie->getDirectors().insert(me_.lock());
}