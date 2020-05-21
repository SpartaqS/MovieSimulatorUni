/* Director declaration
*/

#include "director.hpp"

Director::Director(const string& given_name)
{
	name = given_name;
}

Director::Director(const Director& director)
{
	name = director.name;
	portfolio = director.portfolio;
	// employ this into all movies that person is working on
	wp_MovieList::iterator MovieListIter;
	for (MovieListIter = portfolio.begin(); MovieListIter != portfolio.end(); MovieListIter++)
	{
		//MovieListIter->lock()->employ(std::make_shared<Director>(*this));
	}
}

/*Director::~Director()
{
	//empty because Base Destructor takes care of everything
}*/