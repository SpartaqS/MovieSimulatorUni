/* Director declaration
*/
#include "director.hpp"
#include "movie.hpp"

Director::Director(const string& given_name) : Person(given_name) {}

/*Director::~Director()
{
	//nonexistent because Base Destructor takes care of everything
}*/

void Director::quitMovie(wp_Movie movie)
{
	if (movie.lock()->isWorkingForThisMovie(me_.lock())) //if not: do nothing
	{
		for (sp_Scene sel_scene : movie.lock()->getScenario())
			sel_scene->directorRemove(me_.lock());
		movie.lock()->getDirectors().erase(me_.lock());
		portfolio.erase(movie.lock());
	}
}

void Director::movieAdd(wp_Movie movie)
{
	portfolio.insert(movie.lock());
	movie.lock()->getDirectors().insert(me_.lock());
}