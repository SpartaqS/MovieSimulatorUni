/* Preliminary Project : Interactive Mode
	Gabriel Skowron-Rodriguez */
#include <iostream>
#include <sstream> // to test returned "ostream"s
#include "movie.hpp"

#include <algorithm>
#include <vector>
using sp_MovieVector = std::vector<sp_Movie>;
using sp_ActorVector = std::vector<sp_Actor>;
using sp_DirectorVector = std::vector<sp_Director>;

bool SelectEmployedActor(sp_Movie movie, sp_Actor selectedActor);

int main()
{
	sp_MovieVector AllMovies_;
	sp_ActorVector AllActors_;
	sp_DirectorVector AllDirectors_;
	std::cout << "Welcome to the interactive stuff\n";
	for (string input_ = ""; input_ != "EXIT"; )
	{
		std::cout << "MAIN MENU:\n";
		std::cout << "Enter command:";
		std::getline(std::cin, input_);
		if (input_ == "show movies")
		{
			int size = AllMovies_.size();
			int number = 0;
			for (sp_Movie sel : AllMovies_)
			{
				std::cout << number << ".:" << sel->getTitle() << "\n";
				++number;
			}
			if (size == 0)
				std::cout << "No Movies! You may want to create a new one...\n";
			else
			{
				int selected = size;
				do
				{
					std::cout << "Select a movie by typing its number (\"-1\" to return to main menu):";
					selected = size;
					std::cin >> selected;
					if (selected >= size)
					{
						std::cout << "inserted number is too large!\n";
					}// INTERACT WITH MOVIE TODO
					else if (selected < size && selected >= 0) // Do stuff with movies
					{
						std::cout <<"\n"<< AllMovies_[selected]->getTitle() << ",\" a \"" << AllMovies_[selected]->getGenre() << "\" movie\n";
						// DO INTERACTIONS
					}
				} while (selected >= 0);
				std::cout << "Returning to main menu\n";
			}
		}
		else if (input_ == "add movie")
		{
			std::cout << "Creating a new movie.\nEnter the title:";
			string title;
			std::getline(std::cin, title);
			std::cout << "Enter the genre:";
			string genre;
			std::getline(std::cin, genre);
			AllMovies_.push_back(Movie::createMovie(title,genre));
			std::cout << "New movie called:\"" << title << "\" of \"" << genre << "\" genre created successfuly!\n";

		}
		else if (input_ == "show actors")
		{
			int size = AllActors_.size();
			int number = 0;
			for (sp_Actor sel : AllActors_)
			{
				std::cout << number << ".:" << sel->getName() << "\n";
				++number;
			}
			if (size == 0)
				std::cout << "No Actors! You may want to create a new one...\n";
			else
			{
				int selected = size;
				do
				{
					std::cout << "Select an actor by typing their number (\"-1\" to return to main menu):";
					selected = size;
					std::cin >> selected;
					if (selected >= size)
					{
						std::cout << "inserted number is too large!\n";
					}
					else if (selected < size && selected >= 0)
					{
						std::cout << AllActors_[selected]->getName();
						if (AllActors_[selected]->getPortfolio().size() > 0)
						{
							std::cout << " directs the following movies:\n";
							for (sp_Movie sel_movie : AllActors_[selected]->getPortfolio())
							{
								std::cout << sel_movie->getTitle() << "\n";
							}
						}
						else
						{
							std::cout << " does not direct any movies\n";
						}
					}
				} while (selected >= 0);
				std::cout << "Returning to main menu\n";
			}
		}
		else if (input_ == "add actor")
		{
			std::cout << "Creating a new actor.\nEnter their name:";
			string name;
			std::getline(std::cin, name);
			AllActors_.push_back(Actor::createActor(name));
			std::cout << "New actor called:\"" << name << "\" created successfuly!\n";
		}
		else if (input_ == "show directors")
		{
			int size = AllDirectors_.size();
			int number = 0;
			for (sp_Director sel : AllDirectors_)
			{
				std::cout << number << ".:" << sel->getName() << "\n";
				++number;
			}
			if (size == 0)
				std::cout << "No Directors! You may want to create a new one...\n";
			else
			{
				int selected = size;
				do
				{
					std::cout << "Select a director by typing their number (\"-1\" to return to main menu):";
					selected = size;
					std::cin >> selected;
					if (selected >= size)
					{
						std::cout << "inserted number is too large!\n";
					}
					else if (selected < size && selected >= 0)
					{
						std::cout << AllDirectors_[selected]->getName();
						if (AllDirectors_[selected]->getPortfolio().size() > 0)
						{
						std::cout << " directs the following movies:\n";
							for (sp_Movie sel_movie : AllDirectors_[selected]->getPortfolio())
							{
								std::cout << sel_movie->getTitle() << "\n";
							}
						}
						else
						{
							std::cout << " does not direct any movies\n";
						}
					}
				} while (selected >= 0);
				std::cout << "Returning to main menu\n";
			}
		}
		else if (input_ == "add director")
		{
			std::cout << "Creating a new director.\nEnter their name:";
			string name;
			std::getline(std::cin, name);
			AllDirectors_.push_back(Director::createDirector(name));
			std::cout << "New director called:\"" << name << "\" created successfuly!\n";
		}
		else if (input_ == "EXIT")
		{
			std::cout << "Detected \"EXIT\" command, quitting the application...\n";
		}
		// did not recognize the command
		else
		{
			std::cout << "Unkown command:\"" << input_ << "\" try again\n";
		}
	}
	return 0;
}

bool SelectEmployedActor(sp_Movie movie, sp_Actor selectedActor) // true - success, false - error
{
	sp_ActorVector Cast_;
	std::copy(movie->getCast().begin(), movie->getCast().end(), Cast_.begin()); // copying set to temporary vector for easier use
	int size = Cast_.size();
	int number = 0;
	if (size == 0)
	{
		std::cout << "No Actors! You may want to employ one...\n";
		return false;
	}
	for (sp_Actor sel : Cast_) // display all actors working for movie
	{
		std::cout << number << ".:" << sel->getName() << "\n";
		++number;
	}
	int selected = size;
	do
	{
		std::cout << "Select an actor by typing their number (\"-1\" to cancel and return to main menu):";
		selected = size;
		std::cin >> selected;
		if (selected >= size)
		{
			std::cout << "inserted number is too large!\n";
		}
		else if (selected < size && selected >= 0)
		{
			selectedActor = Cast_[selected];
			return true;
		}
	} while (selected >= 0);
	std::cout << "Cancelled selection! Returning to main menu\n";
	return false;
}