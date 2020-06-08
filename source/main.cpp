/* Preliminary Project : Interactive Mode
	Gabriel Skowron-Rodriguez */
#include <iostream>
#include <sstream> // to test returned "ostream"s
#include "movie.hpp"

// Stuff needed for interactive mode START
#include <algorithm>
#include <vector>
using sp_MovieVector = std::vector<sp_Movie>;
using sp_ActorVector = std::vector<sp_Actor>;
using sp_DirectorVector = std::vector<sp_Director>;
using sp_CharactersVector = std::vector<sp_Character>;

bool SelectEmployedActor(sp_Movie movie, sp_Actor& selectedActor);
bool SelectCharacterActor(sp_Character character, sp_Actor& selectedActor);
bool SelectEmployedDirector(sp_Movie movie, sp_Director& selectedDirector);
bool SelectMovieCharacter(sp_Movie movie, sp_Character& selectedCharacter);
bool SelectMovieScene(sp_Movie movie, sp_Scene& selectedScene);
bool SelectSceneDirector(sp_Scene scene, sp_Director& selectedDirector);

// Stuff needed for interactive mode END

int main(int argc, char * argv[])
{
	string menuHelp = "\nAvaliable commands:\n show movies\n add movie\n show actors\n add actor\n show directors\n add director\n EXIT\n";
	string movieHelp = "\nAvaliable commands:\n fire actor\n add actor\n swap roles\n show actors\n fire director\n add director\n show directors\n delete character\n create character\n show characters\n delete scene\n create scene\n show scenes\n swap scenes\n play\n credits\n BACK\n";
	string characterHelp = "\nAvaliable commands:\n remove actor\n add actor\n show actors\n set name\n set description\n BACK\n";
	string sceneHelp = "\nAvaliable commands:\n remove director\n add director\n show directors\n replace character\n replace at position\n show characters\n set name\n play\n BACK";
	sp_MovieVector AllMovies_;
	sp_ActorVector AllActors_;
	sp_DirectorVector AllDirectors_;

	if (argc == 2)
	{
		string enteredCommand = argv[1];
		if (enteredCommand == "-h")
		{
			std::cout << "Gabriel Skowron-Rodriguez, modified on 08.06.2020 using:\n";
			std::cout << "_MSC_VER : 1916 \n_MSC_FULL_VER : 191627035 \n_MSC_BUILD : 0 \n";
			std::cout << "Main Menu commands:\n" << menuHelp << "Movie Commands:\n" << movieHelp << "Character Commands:\n" << characterHelp << "Scene Commands:\n" << sceneHelp;
			return 0;
		}
	}

	AllMovies_.push_back(Movie::createMovie("testTitle", "testGenre"));
	AllActors_.push_back(Actor::createActor("Adam Actual"));
	AllActors_.push_back(Actor::createActor("Berry Bronzesmith"));
	AllDirectors_.push_back(Director::createDirector("testDirector"));
	AllMovies_.front()->characterCreate("Gillian", "Super soldier");
	AllMovies_.front()->characterCreate("Edward", "Super hero");
	AllMovies_.front()->characterCreate("Josh", "Super citizen");
	for (sp_Actor temp : AllActors_)
		AllMovies_.front()->employ(temp);
	for (sp_Director temp : AllDirectors_)
		AllMovies_.front()->employ(temp);

	std::cout << "Welcome to the interactive stuff\n";
	for (string input_ = ""; input_ != "EXIT"; )
	{
		std::cout << menuHelp << "MAIN MENU:\n";
		std::cout << "Enter command:";
		std::getline(std::cin, input_);
		if (input_ == "show movies")
		{
			int size = AllMovies_.size();
			if (size == 0)
				std::cout << "No Movies! You may want to create a new one...\n";
			else
			{
				int selected = size;
				do
				{
					std::cout << "Movies:\n";
					int number = 0;
					for (sp_Movie sel : AllMovies_)
					{
						std::cout << number << ".:" << sel->getTitle() << "\n";
						++number;
					}
					std::cout << "Select a movie by typing its number (\"-1\" to return to main menu):";
					selected = size;
					std::cin >> selected;
					if (selected >= size)
					{
						std::cout << "inserted number is too large!\n";
					}// INTERACT WITH MOVIE TODO
					else if (selected < size && selected >= 0) // Do stuff with movies
					{
						sp_Movie movie = AllMovies_[selected];
						// DO INTERACTIONS
						string buffer_clearer;
						std::getline(std::cin, buffer_clearer); // clearing the buffer (not doing so causes "double input")
						for (string m_input_ = ""; m_input_ != "BACK"; )
						{
							std::cout << "\n" << movieHelp << "\n\"" << movie->getTitle() << "\", a \"" << movie->getGenre() << "\" movie\n";
							std::cout << "Enter command (\"BACK\" to go back to movie selection):";
							std::getline(std::cin, m_input_);
							if (m_input_ == "show actors")
							{
								if (movie->getCast().size() > 0)
								{
									std::cout << "Employed actors:\n";
									for (sp_Actor sel : movie->getCast())
										std::cout << "   " << sel->getName() << "\n";
								}
								else
								{
									std::cout << "No actors employed!\n";
								}
							}
							else if (m_input_ == "fire actor")
							{
								sp_Actor toFire;
								if (movie->getCast().size() > 0)
									std::cout << "Choose an actor to fire\n";
								if (SelectEmployedActor(movie, toFire) == true)
								{
									std::cout << "are you sure? (\"Y\" to confirm):";
									string confirmation = "";
									std::cin >> confirmation;
									if (confirmation == "Y")
									{
										movie->fire(toFire);
										std::cout << toFire->getName() << "has been fired!\n";
									}
									else
									{
										std::cout << "Firing cancelled\n";
									}
								}
							}
							else if (m_input_ == "add actor")
							{
								sp_ActorsList AllNotMovieActorsTemp_; // temporary vector of Actors who are not employed in this movie
								sp_ActorVector ActorsToRemove;
								std::copy(AllActors_.begin(), AllActors_.end(), std::back_inserter(AllNotMovieActorsTemp_));
								for (sp_Actor inMovie : movie->getCast()) // removing all actors from who already work in this movie 
								{
									for (sp_Actor toKickout : AllNotMovieActorsTemp_)
									{
										if (toKickout == inMovie)
										{
											AllNotMovieActorsTemp_.remove(toKickout); // remove the actor from temporary list
											break;
										}
									}
								}
								sp_ActorVector AllNotMovieActors_;
								std::copy(AllNotMovieActorsTemp_.begin(), AllNotMovieActorsTemp_.end(), std::back_inserter(AllNotMovieActors_)); // convert list to vector for easier management
								AllNotMovieActorsTemp_.clear(); // dispose of temporary pointers
								int AllNotMovieActors_size = AllNotMovieActors_.size();
								int number = 0;
								for (sp_Actor sel : AllNotMovieActors_)
								{
									std::cout << number << ".:" << sel->getName() << "\n";
									++number;
								}
								if (AllNotMovieActors_size == 0)
									std::cout << "No Actors! You may want to create a new one...\n";
								else
								{
									int sel_actor = AllNotMovieActors_size;
									do
									{
										std::cout << "Select an actor to employ by typing their number (\"-1\" to return to movie menu):";
										sel_actor = AllNotMovieActors_size;
										std::cin >> sel_actor;
										if (sel_actor >= AllNotMovieActors_size)
										{
											std::cout << "inserted number is too large!\n";
										}
										else if (sel_actor < AllNotMovieActors_size && sel_actor >= 0)
										{
											if (movie->isWorkingForThisMovie(AllNotMovieActors_[sel_actor]) == false)
											{
												movie->employ(AllNotMovieActors_[sel_actor]);
												std::cout << AllNotMovieActors_[sel_actor]->getName() << " employed successfully\n";
												sel_actor = -1;
											}
											else
											{
												std::cout << "Actor already works for this movie!\n";
											}

										}
									} while (sel_actor >= 0);
									std::cout << "Returning to movie menu\n";
								}
							}
							else if (m_input_ == "swap roles")
							{
								sp_Actor toSwap1, toSwap2;
								if (movie->getCast().size() > 0)
									std::cout << "Choose an actor to swap\n";
								if (SelectEmployedActor(movie, toSwap1) == true)
								{
									std::cout << "Choose the second actor to swap\n";
									if (SelectEmployedActor(movie, toSwap2) == true)
									{
										if (toSwap1 == toSwap2)
											std::cout << "Selected the same actor twice! Returning to previous menu";
										else
										{
											movie->actorRoleSwap(toSwap1, toSwap2);
											std::cout << "Swapped roles of " << toSwap1->getName() << " and " << toSwap2->getName() << "\n";
										}
									}
								}
							}
							else if (m_input_ == "show directors")
							{
								if (movie->getDirectors().size() > 0)
								{
									std::cout << "Employed directors:\n";
									for (sp_Director sel : movie->getDirectors())
										std::cout << sel->getName() << "\n";
								}
								else
								{
									std::cout << "No directors employed!\n";
								}
							}
							else if (m_input_ == "fire director")
							{
								sp_Director toFire;
								if (movie->getDirectors().size() > 0)
									std::cout << "Choose a director to fire\n";
								if (SelectEmployedDirector(movie, toFire) == true)
								{
									std::cout << "are you sure? (\"Y\" to confirm):";
									string confirmation = "";
									std::cin >> confirmation;
									if (confirmation == "Y")
									{
										movie->fire(toFire);
										std::cout << toFire->getName() << "has been fired!\n";
									}
									else
									{
										std::cout << "Firing cancelled\n";
									}
								}
							}
							else if (m_input_ == "add director")
							{
								sp_DirectorsList AllNotMovieDirectorsTemp_; // temporary vector of Actors who are not employed in this movie
								sp_DirectorVector ActorsToRemove;
								std::copy(AllDirectors_.begin(), AllDirectors_.end(), std::back_inserter(AllNotMovieDirectorsTemp_));
								for (sp_Director inMovie : movie->getDirectors()) // removing all actors from who already work in this movie 
								{
									for (sp_Director toKickout : AllNotMovieDirectorsTemp_)
									{
										if (toKickout == inMovie)
										{
											AllNotMovieDirectorsTemp_.remove(toKickout); // remove the actor from temporary list
											break;
										}
									}
								}
								sp_DirectorVector AllNotMovieDirectors_;
								std::copy(AllNotMovieDirectorsTemp_.begin(), AllNotMovieDirectorsTemp_.end(), std::back_inserter(AllNotMovieDirectors_)); // convert list to vector for easier management
								AllNotMovieDirectorsTemp_.clear(); // dispose of temporary pointers
								int AllDirectors_size = AllNotMovieDirectors_.size();
								int number = 0;
								for (sp_Director sel : AllNotMovieDirectors_)
								{
									std::cout << number << ".:" << sel->getName() << "\n";
									++number;
								}
								if (AllDirectors_size == 0)
									std::cout << "No Directors! You may want to create a new one...\n";
								else
								{
									int sel_director = AllDirectors_size;
									do
									{
										std::cout << "Select a director to employ by typing their number (\"-1\" to return to movie menu):";
										sel_director = AllDirectors_size;
										std::cin >> sel_director;
										if (sel_director >= AllDirectors_size)
										{
											std::cout << "inserted number is too large!\n";
										}
										else if (sel_director < AllDirectors_size && sel_director >= 0)
										{
											if (movie->isWorkingForThisMovie(AllNotMovieDirectors_[sel_director]) == false)
											{
												movie->employ(AllNotMovieDirectors_[sel_director]);
												std::cout << AllNotMovieDirectors_[sel_director]->getName() << " employed successfully\n";
												sel_director = -1;
											}
											else
											{
												std::cout << "Director already works for this movie!\n";
											}

										}
									} while (sel_director >= 0);
									std::cout << "Returning to movie menu\n";
								}
							}
							// Characters sub-menu
							else if (m_input_ == "show characters")
							{
								if (movie->getCharacters().size() > 0)
								{
									std::cout << "Movie Characters:\n";
									sp_Character selectedCharacter;
									if (SelectMovieCharacter(movie, selectedCharacter))
									{
										string buffer_clearer;
										std::getline(std::cin, buffer_clearer); // clearing the buffer (not doing so causes "double input")
										for (string c_input_ = ""; c_input_ != "BACK"; )
										{
											std::cout << characterHelp << "\ncharacter:\"" << selectedCharacter->getName() << "\"\n";
											std::cout << "Enter command (\"BACK\" to go back to movie menu):";
											std::getline(std::cin, c_input_);
											if (c_input_ == "remove actor")
											{
												sp_Actor toRemove;
												if (selectedCharacter->getActorsList().size() > 0)
												{
													std::cout << "Choose an actor to remove from playing as " << selectedCharacter->getName() << "\n";
													if (SelectCharacterActor(selectedCharacter, toRemove) == true)
													{
														selectedCharacter->actorRemove(toRemove);
														std::cout << toRemove->getName() << " no longer plays the role of " << selectedCharacter->getName() << "\n";
													}
												}
												else
												{
													std::cout << "No actors play this character! You may want to assign at least one...\n";
												}
											}
											else if (c_input_ == "add actor")
											{
												sp_Actor toAdd;
												if (movie->getCast().size() > 0)
													std::cout << "Choose an actor to add assign the role of " << selectedCharacter->getName() << "\n";
												if (SelectEmployedActor(movie, toAdd) == true)
												{
													try {
														selectedCharacter->actorAdd(toAdd);
													}
													catch (std::runtime_error)
													{
														std::cout << "Chosen Actor already plays this role! Cancelling...\n";
														break;
													}
													std::cout << toAdd->getName() << " now plays the role of " << selectedCharacter->getName() << "\n";
												}
											}
											else if (c_input_ == "show actors")
											{
												std::cout << "actors playing this as " << selectedCharacter->getName() << "\n";
												for (sp_Actor temp : selectedCharacter->getActorsList())
												{
													std::cout << "  " << temp->getName() << "\n";
												}
											}
											else if (c_input_ == "set name")
											{
												string c_name_input_ = "";
												std::cout << "Enter new name for this character:";
												std::getline(std::cin, c_name_input_);
												if (c_name_input_ != "")
												{
													bool is_c_name_valid = true;
													for (sp_Character selected : movie->getCharacters())
													{
														if (selected->getName() == c_name_input_)
															is_c_name_valid = false;
													}
													if (is_c_name_valid)
														selectedCharacter->setName(c_name_input_);
													else
														std::cout << "There already exists a character with name:\"" << c_name_input_ << "\"! Name setting cancelled!";
												}
												else
												{
													std::cout << "Name setting cancelled!";
												}
											}
											else if (c_input_ == "set description")
											{
												string c_description_input_ = "";
												std::cout << "Enter new description for this character:";
												std::getline(std::cin, c_description_input_);
												if (c_description_input_ != "")
												{
													selectedCharacter->setDescription(c_description_input_);
												}
												else
												{
													std::cout << "Description setting cancelled!";
												}
											}
											else if (c_input_ == "BACK")
											{
												std::cout << "Detected \"BACK\" command, returning to movie menu.\n";
											}
											// did not recognize the command
											else
											{
												std::cout << "Unkown command:\"" << c_input_ << "\" try again\n";
											}
										}
									}
									else
									{
										std::cout << "No character selected! Back to movie menu\n";
									}
								}
								else
								{
									std::cout << "This movie has no characters!\n";
								}
							}
							else if (m_input_ == "delete character")
							{
								sp_Character toDelete;
								if (SelectMovieCharacter(movie, toDelete))
								{
									std::cout << "Character \"" << toDelete->getName() << "\" has been deleted!\n";
									movie->remove(toDelete);
								}
								else
								{
									std::cout << "Deletion cancelled\n";
								}
							}
							else if (m_input_ == "create character")
							{
								string name = "";
								while (name == "")
								{
									std::cout << "Creating a new character.\nEnter the name:";
									std::getline(std::cin, name);
								}
								string description = "";
								while (description == "")
								{
									std::cout << "Enter the description:";
									std::getline(std::cin, description);
								}
								movie->characterCreate(name, description);
								std::cout << "New character called:\"" << movie->getCharacters().back()->getName() << "\" described as: \"" << description << "\" created successfuly!\n";
								if (movie->getCharacters().back()->getName() != name)
									std::cout << "Warning! Character with provided name already exists. The newest character has been renamed to: \"" << movie->getCharacters().back()->getName() << "\"\n";
							}
							else if (m_input_ == "delete scene")
							{
								sp_Scene toDelete;
								if (SelectMovieScene(movie, toDelete))
								{
									std::cout << "Character \"" << toDelete->getName() << "\" has been deleted!\n";
									movie->sceneDelete(toDelete);
								}
								else
								{
									std::cout << "Deletion cancelled\n";
								}
							}
							else if (m_input_ == "create scene")
							{
								string s_name = "";
								while (s_name == "")
								{
									std::cout << "Creating a new scene.\nEnter the name:";
									std::getline(std::cin, s_name);
								}
								string s_description = "";
								while (s_description == "")
								{
									std::cout << "Enter the scene's description:";
									std::getline(std::cin, s_description);
								}
								sp_Director s_director;
								if (SelectEmployedDirector(movie, s_director))
								{
									size_t total_s_characters = Scene::specialCharactersInString(s_description);
									if (total_s_characters > 0) // ask for characters list
									{
										sp_CharactersVector s_characters;
										sp_Character s_character;
										while (s_characters.size() < total_s_characters && SelectMovieCharacter(movie, s_character))
										{
											s_characters.push_back(s_character);
										}
										if (s_characters.size() == total_s_characters)
											movie->sceneCreate(s_name, s_description, s_director, s_characters);
										else
										{
											std::cout << "Scene creation has been cancelled!\n";
											break;
										}
									}
									else // create a scene without Characters
									{
										movie->sceneCreate(s_name, s_description, s_director);
									}
									std::cout << "New scene named: \"" << movie->getScenario().back()->getName() << "\" created successfuly!\n";
									if (movie->getScenario().back()->getName() != s_name)
										std::cout << "Warning! Scene with provided name already exists. The newest scene has been renamed to: \"" << movie->getScenario().back()->getName() << "\"\n";
								}
							}
							// Scenes sub-menu
							else if (m_input_ == "show scenes")
							{
								if (movie->getScenario().size() > 0)
								{
									std::cout << "Movie Scenario:\n";
									sp_Scene selectedScene;
									if (SelectMovieScene(movie, selectedScene))
									{
										string buffer_clearer;
										std::getline(std::cin, buffer_clearer); // clearing the buffer (not doing so causes "double input")
										for (string c_input_ = ""; c_input_ != "BACK"; )
										{
											std::cout << sceneHelp << "\nScene:\"" << selectedScene->getName() << "\", description:\n" << selectedScene->getDescription() << "\"\n";
											std::cout << "Enter command (\"BACK\" to go back to movie menu):";
											std::getline(std::cin, c_input_);
											if (c_input_ == "remove director")
											{
												sp_Director toRemove;
												if (selectedScene->getSceneDirectorsList().size() > 0)
												{
													std::cout << "Choose an actor to remove from playing as " << selectedScene->getName() << "\n";
													if (SelectSceneDirector(selectedScene, toRemove) == true)
													{
														selectedScene->directorRemove(toRemove);
														std::cout << toRemove->getName() << " no longer directs the \"" << selectedScene->getName() << "\" scene\n";
													}
												}
												else
												{
													std::cout << "No directors direct this scene! You may want to assign at least one for the scene to be playable...\n";
												}
											}
											else if (c_input_ == "add director")
											{
												sp_Director toAdd;
												if (movie->getDirectors().size() > 0)
													std::cout << "Choose a director to add assign the role of " << selectedScene->getName() << "\n";
												if (SelectEmployedDirector(movie, toAdd) == true)
												{
													try {
														selectedScene->directorAdd(toAdd);
													}
													catch (std::runtime_error)
													{
														std::cout << "Chosen Director already directs this scene! Cancelling...\n";
														break;
													}
													std::cout << toAdd->getName() << " now directs the \"" << selectedScene->getName() << "\" scene\n";
												}
											}
											else if (c_input_ == "show directors")
											{
												std::cout << "directors directing \"" << selectedScene->getName() << "\" scene\n";
												for (sp_Director temp : selectedScene->getSceneDirectorsList())
												{
													std::cout << "  " << temp->getName() << "\n";
												}
											}
											else if (c_input_ == "replace character") 												
											{
												sp_Character toReplace,withWhom;
												std::cout << "Select Character to replace:\n";
												if (SelectMovieCharacter(movie, toReplace))
												{
													std::cout << "Select Character who will replace the chosen one:\n";
													if (SelectMovieCharacter(movie, withWhom))
													{
														selectedScene->replace(toReplace, withWhom);
														std::cout << "Character replaced!";
													}
													else
													{
														std::cout << "replacing at position has been cancelled!";
													}
												}
												else
												{
													std::cout << "replacing at position has been cancelled!";
												}
											}
											else if (c_input_ == "replace at position")
											{
												unsigned int slot = selectedScene->getSceneCharacters().size();
												while (slot >= selectedScene->getSceneCharacters().size())
												{
													slot = selectedScene->getSceneCharacters().size();
													std::cout << "Which character should be replaced (provide a number from 0 up to " << selectedScene->getSceneCharacters().size() -1  << " included):";
													std::cin >> slot;
												}
												sp_Character withWhom;
												if (SelectMovieCharacter(movie, withWhom))
												{
													selectedScene->replace(slot, withWhom);
												}
												else
												{
													std::cout << "replacing at position has been cancelled!";
												}
											}
											else if (c_input_ == "show characters")
											{
												std::cout << "characters in this scene: \"" << selectedScene->getName() << "\" scene\n";
												unsigned int num = 0;
												for (sp_Character temp : selectedScene->getSceneCharacters())
												{
													std::cout << "  " << num << ".:\"" << temp->getName() << "\"\n";
													++num;
												}
											}
											else if (c_input_ == "set name")
											{
												string s_name_input_ = "";
												std::cout << "Enter new name for this scene:";
												std::getline(std::cin, s_name_input_);
												if (s_name_input_ != "")
												{
													bool is_s_name_valid = true;
													for (sp_Scene selected : movie->getScenario())
													{
														if (selected->getName() == s_name_input_)
															is_s_name_valid = false;
													}
													if (is_s_name_valid)
														selectedScene->setName(s_name_input_);
													else
														std::cout << "There already exists a scene with name:\"" << s_name_input_ << "\"! Name setting cancelled!";
												}
												else
												{
													std::cout << "Name setting cancelled!";
												}
											}
											else if (c_input_ == "play")
											{
												std::stringstream os;
												os.str("");
												os << *selectedScene;
												std::cout << os.str();
											}
											// did not recognize the command
											else
											{
												std::cout << "Unkown command:\"" << c_input_ << "\" try again\n";
											}
										}
									}
									else
									{
										std::cout << "No scene selected! Back to movie menu\n";
									}
								}
								else
								{
									std::cout << "This movie has no scenes!\n";
								}
							}
							else if (m_input_ == "swap scenes")
							{
								sp_Scene scene1, scene2;
								std::cout << "Select Scene to swap:\n";
								if (SelectMovieScene(movie, scene1))
								{
									std::cout << "Select the second Scene to swap:\n";
									if (SelectMovieScene(movie, scene2))
									{
										movie->sceneSwap(scene1, scene2);
										std::cout << "Scenes swapped!";
									}
									else
									{
										std::cout << "Scene swapping has been cancelled!";
									}
								}
								else
								{
									std::cout << "Scene swapping has been cancelled!";
								}
							}
							else if (m_input_ == "play")
							{
								std::stringstream os;
								os.str("");
								movie->play(os);
								std::cout << os.str();
							}
							else if (m_input_ == "credits")
							{
								std::stringstream os;
								os.str("");
								movie->credits(os);
								std::cout << os.str();
							}
							else if (m_input_ == "BACK")
							{
								std::cout << "Detected \"BACK\" command, returning to movie selection.\n";
							}
							// did not recognize the command
							else
							{
							std::cout << "Unkown command:\"" << m_input_ << "\" try again\n";
							}
						}
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
			if (size == 0)
				std::cout << "No Actors! You may want to create a new one...\n";
			else
			{
				int selected = size;
				do
				{
					for (sp_Actor sel : AllActors_)
					{
						std::cout << number << ".:" << sel->getName() << "\n";
						++number;
					}
					std::cout << "See portfolios:\nSelect an actor by typing their number (\"-1\" to return to main menu):";
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
							std::cout << " acts in the following movies:\n";
							for (sp_Movie sel_movie : AllActors_[selected]->getPortfolio())
							{
								std::cout << sel_movie->getTitle() << "\n";
							}
						}
						else
						{
							std::cout << " does not act any movies\n";
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
				std::cout << "   " << number << ".:" << sel->getName() << "\n";
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

bool SelectEmployedActor(sp_Movie movie, sp_Actor& selectedActor) // true - success, false - error
{
	sp_ActorVector Cast_;
	std::copy(movie->getCast().begin(), movie->getCast().end(), std::back_inserter(Cast_)); // copying set to temporary vector for easier use
	int size = Cast_.size();
	int number = 0;
	if (size == 0)
	{
		std::cout << "No Actors! You may want to employ one...\n";
		return false;
	}
	for (sp_Actor sel : Cast_) // display all actors working for movie
	{
		std::cout << "  " << number << ".:" << sel->getName() << "\n";
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
	std::cout << "Cancelled selection! Returning to previous menu\n";
	return false;
}

bool SelectCharacterActor(sp_Character character, sp_Actor& selectedActor) // true - success, false - error
{
	sp_ActorVector Cast_;
	std::copy(character->getActorsList().begin(), character->getActorsList().end(), std::back_inserter(Cast_)); // copying set to temporary vector for easier use
	int size = Cast_.size();
	int number = 0;
	if (size == 0)
	{
		std::cout << "No Actors! You may want to assign one to this character...\n";
		return false;
	}
	for (sp_Actor sel : Cast_) // display all actors playing this scene
	{
		std::cout << "  " << number << ".:" << sel->getName() << "\n";
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
	std::cout << "Cancelled selection! Returning to previous menu\n";
	return false;
}

bool SelectEmployedDirector(sp_Movie movie, sp_Director& selectedDirector) // true - success, false - error
{
	sp_DirectorVector Directors_;
	std::copy(movie->getDirectors().begin(), movie->getDirectors().end(), std::back_inserter(Directors_)); // copying set to temporary vector for easier use
	int size = Directors_.size();
	int number = 0;
	if (size == 0)
	{
		std::cout << "No Directors! You may want to employ one...\n";
		return false;
	}
	for (sp_Director sel : Directors_) // display all actors working for movie
	{
		std::cout << "  " << number << ".:" << sel->getName() << "\n";
		++number;
	}
	int selected = size;
	do
	{
		std::cout << "Select a director by typing their number (\"-1\" to cancel and return to main menu):";
		selected = size;
		std::cin >> selected;
		if (selected >= size)
		{
			std::cout << "inserted number is too large!\n";
		}
		else if (selected < size && selected >= 0)
		{
			selectedDirector = Directors_[selected];
			return true;
		}
	} while (selected >= 0);
	std::cout << "Cancelled selection! Returning to prevoius menu\n";
	return false;
}

bool SelectMovieCharacter(sp_Movie movie, sp_Character& selectedCharacter) // true - success, false - cancelled
{
	sp_CharactersVector Characters_;
	std::copy(movie->getCharacters().begin(), movie->getCharacters().end(), std::back_inserter(Characters_)); // copying set to temporary vector for easier use
	int size = Characters_.size();
	if (size == 0)
	{
		std::cout << "No Characters! You may want to create one...\n";
		return false;
	}
	for (sp_Character sel : Characters_) // display all characters
	{
		std::cout << "  \"" << sel->getName() << "\"\n";
	}
	bool selected = false;
	string c_name = "";
	do
	{
		std::cout << "Select a Character by typing their name (enter \"-1\" to return the previous menu):";
		std::cin >> c_name;
		if (c_name != "-1")
		{
			try
			{
				selected = true;
				selectedCharacter = movie->character(c_name);
			}
			catch (std::runtime_error&) // no exception: will exit the do {} while() loop
			{ 
				std::cout << "no character with such name! try again.\n";
				selected = false;
			}
		}
		else
		{
			std::cout << "Cancelled selection! Returning to main menu\n";
			return false;
		}
	} while (selected == false);
	return true;
}

bool SelectMovieScene(sp_Movie movie, sp_Scene& selectedScene) // true - success, false - cancelled
{
	for (sp_Scene sel : movie->getScenario()) // display all characters
	{
		std::cout << "  \"" << sel->getName() << "\"\n";
	}
	bool selected = false;
	string s_name = "";
	do
	{
		std::cout << "Select a Scene by typing its name (enter \"-1\" to return the previous menu):";
		std::cin >> s_name;
		if (s_name != "-1")
		{
			try
			{
				selected = true;
				selectedScene = movie->scene(s_name);
			}
			catch (std::runtime_error&) // no exception: will exit the do {} while() loop
			{
				std::cout << "no scene with such name! try again.\n";
				selected = false;
			}
		}
		else
		{
			std::cout << "Cancelled scene selection! Returning to main menu\n";
			return false;
		}
	} while (selected == false);
	return true;
}

bool SelectSceneDirector(sp_Scene scene, sp_Director& selectedDirector) // true - success, false - error
{
	sp_DirectorVector Dirs_;
	int size = scene->getSceneDirectorsList().size();
	int number = 0;
	if (size == 0)
	{
		std::cout << "No Directors! You may want to assign one for this scene to be playable...\n";
		return false;
	}
	if (size > 1)
		std::copy(scene->getSceneDirectorsList().begin(), scene->getSceneDirectorsList().end(), std::back_inserter(Dirs_)); // copying set to temporary vector for easier use
	else
	{
		Dirs_.push_back(scene->getSceneDirectorsList().front());
	}
	for (sp_Director sel : Dirs_) // display all directors directing this scene
	{
		std::cout << "  " << number << ".:" << sel->getName() << "\n";
		++number;
	}
	int selected = size;
	do
	{
		std::cout << "Select a director by typing their number (\"-1\" to cancel and return to main menu):";
		selected = size;
		std::cin >> selected;
		if (selected >= size)
		{
			std::cout << "inserted number is too large!\n";
		}
		else if (selected < size && selected >= 0)
		{
			selectedDirector = Dirs_[selected];
			return true;
		}
	} while (selected >= 0);
	std::cout << "Cancelled selection! Returning to previous menu\n";
	return false;
}