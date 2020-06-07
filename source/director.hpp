/* Director:
	At least one is needed for a Scene to be played.
	Can work on many movies
*/
#ifndef director_hpp
#define director_hpp

#include "person.hpp"

class Director;
using sp_Director = std::shared_ptr<Director>;
using sp_DirectorsList = std::list<sp_Director>;
using sp_DirectorsSet = std::set<sp_Director>;
using wp_Director = std::weak_ptr<Director>;

class Director : public Person
{
public:
	static sp_Director createDirector(const string& given_name)
	{
		sp_Director director = std::make_shared<Director>(given_name);
		director->me_ = director;
		return director;
	};
	Director(const string &given_name); // constructor
	virtual void quitMovie(sp_Movie movie);
	virtual void movieAdd(sp_Movie movie);
	// operator= and copy c-tor make no sense here
	//virtual ~Director(); // destructor -> calls all portfolio movies to act accordingly
private:
	string name;
	sp_MovieSet portfolio;
	wp_Director me_;
};
#endif // !director_hpp