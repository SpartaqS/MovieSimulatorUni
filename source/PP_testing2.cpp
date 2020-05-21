/* Preliminary Project : Testing
	Gabriel Skowron-Rodriguez */

#include <iostream>
#include "movie.hpp"

int main()
{
	Movie movie1("Test Title", "DevStuffGenre");
	movie1.create(Character("Tom", "description")); // LETS USE THE EXISTING ONE
	return 0;
}