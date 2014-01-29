/* Name: Jason Nelson
   Class: CS202 Assignment: Program 3
   Date: 8/6/2013

   File: main.cpp

   This file contains the application for playing my game!
*/

#include "character.h"
#include "dungeon.h"
#include "battle_history.h"
#include "win_rate.h"


int main()
{
	//character * test_char;  Just used to test = operator, not needed for game

	win_rate results; // multi-threaded list to track game results
	character * your_char; // pointer to the players character
	monster * current_monster; // pointer to a monster
	dungeon doom; //the dungeon!

	battle_history * battles; // pointer to a battle_history

        // single chars that hold player choices
	char character_choice;
	char pre_combat;
	char combat;
	
	char * monst_type = NULL; // monster type to be added to the battle history

	int rand_monster; // used to select a random monster		
	int your_atk; // holds the damage the player deals in a round of combat
	int monst_atk; //holds the damage the monster deals in a round of combat

	int monsters = 4; // number of monster types
	int current_floor;


	results.load_data(); // load game results in to list

	results.display_win_percentage(); // display win rate to player


	doom.load_dungeon(); //load the dungeon from a file
	battles = new battle_history; //make a new battle_history

	//Character creation
	cout << "Creating your character!\n\n";
	cout << "Warrior (w) or Thief (t)? ";
	cin >> character_choice;
	cin.ignore(100, '\n');

	switch(character_choice)
	{
		case 'w':
			your_char = new warrior;
			your_char->add_bonus_str();
			break;
		case 't':
			your_char = new thief;
			your_char->add_bonus_dex();
			break;
		default:
			cout << "Fine, you're a warrior.\n";
			your_char = new warrior;
			your_char->add_bonus_str();
			break;
	}
	
	your_char->create_character();
	your_char->introduction();
	cout << *your_char;

	/* 
	*your_char = *your_char;
	cout << *your_char;
	*/

	//Start the game

	cout << "Entering the dungeon!\n\n";

	while(doom.display_next_room() && your_char->get_health() > 0) //continue until the player is dead, or each encounter has been defeated
	{
	
		//choose a random monster!
		srand(time(NULL));
	
		rand_monster = rand() % monsters;

		switch(rand_monster)
		{
			case 1:
				current_monster = new skeleton;
				break;
			case 2:
				current_monster = new ogre;
				break;
			case 3:
				current_monster = new evil_sorcerer;
				break;
			default:
				current_monster = new skeleton;
				break;
		}

		current_monster->greeting();

		// Present player choices
		do
		{
			cout << "What would you like to do?\n";
			cout << "Character info (i), Examine monster (m), Enter combat (c): ";
			cin >> pre_combat;
			cin.ignore(100, '\n');
		
			switch(pre_combat)
			{
				case 'i':
					cout << *your_char;
					break;
				case 'm':
					current_monster->display_monster();
					break;
				case 'c':
					cout << "You move in to battle the monster!\n";
					break;
				default:
					cout << "Invalid command! Try again.\n";
					break;
			}
		}while(pre_combat != 'c');

		//Begin combat
		do
		{
			cout << "Now what?\n";
			cout << "Attack (a), Special attack (s): ";
			cin >> combat;
			cin.ignore(100, '\n');

			switch(combat)
			{
				case 'a':
					if(*your_char >= *current_monster)
					{
						your_atk = your_char->attack();
						current_monster->change_health(-your_atk);
						monst_atk = current_monster->attack();
						your_char->change_health(-monst_atk);
					}
					else
					{
						monst_atk = current_monster->attack();
						your_char->change_health(-monst_atk);
						your_atk = your_char->attack();
						current_monster->change_health(-your_atk);
					}		
					break;
				case 's':
					if(*your_char >= *current_monster)
					{
						your_atk = your_char->special_attack();
						current_monster->change_health(-your_atk);
						monst_atk = current_monster->attack();
						your_char->change_health(-monst_atk);
					}
					else
					{
						monst_atk = current_monster->attack();
						your_char->change_health(-monst_atk);
						your_atk = your_char->special_attack();
						current_monster->change_health(-your_atk);
					}
					break;
				default:
					if(*your_char >= *current_monster)
					{
						your_atk = your_char->attack();
						current_monster->change_health(-your_atk);
						monst_atk = current_monster->attack();
						your_char->change_health(-monst_atk);
					}
					else
					{
						monst_atk = current_monster->attack();
						your_char->change_health(-monst_atk);
						your_atk = your_char->attack();
						current_monster->change_health(-your_atk);
					}		
					break;
			
			}	

		}while( your_char->get_health() > 0 && current_monster->get_health() > 0); //repeat until something dies

		// Add defeated monster to battle history	
		current_floor = doom.get_floor();
		current_monster->get_type(monst_type);
		battles->insert(current_floor, monst_type);

		// clean up defeated monster
		delete [] monst_type;
		delete current_monster;
	}

	// If the player is alive, they won the game
	if(your_char->get_health() > 0)
	{	
		cout << "\nYay you win!\n\n";
		results.save_data('w'); //add win to game results file
	}
	else
	{
		cout << "\nAw, you died.\n\n";
		results.save_data('l'); //add loss to game results file
	}

	// Show the player what they did!
	battles->display_history();	

	delete battles;

	// delete character
	delete your_char;

return 0;
}

