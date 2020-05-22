/* Preliminary Project : Testing
	Gabriel Skowron-Rodriguez */

#include <iostream>
#include "movie.hpp"

int main()
{
	Movie movie1("Test Title", "DevStuffGenre");
	Character char1("Tom", "description");
	movie1.create(char1); // LETS USE THE EXISTING ONE
	std::cout << movie1.getTitle() << "\n";
	return 0;
}