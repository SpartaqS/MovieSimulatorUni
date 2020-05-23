/* Preliminary Project : Testing
	Gabriel Skowron-Rodriguez */

#include <iostream>
#include "movie.hpp"

int main()
{
	Movie movie1("Test Title", "DevStuffGenre");
	std::cout << movie1.getTitle() << "\n";
	movie1.characterCreate("Tom", "description"); // LETS USE THE EXISTING ONE
	std::cout << movie1.character("Tom")->getName() << "\n";
	
	return 0;
}