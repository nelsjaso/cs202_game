/* Name: Jason Nelson
   Date: 7/30/2013
   Class: CS202 Assignment: Program 3

   File: win_rate.cpp

   This file contains the implementations of the classes related 
   to the win_rate data structure.
*/

#include "dungeon.h"
#include "win_rate.h"


// win rate node constructor
winr_node::winr_node()
{
	next = NULL;
	next_win = NULL;

	game_number = 0;
	result = ' ';
}



// win rate node destructor
winr_node::~winr_node()
{
	game_number = 0;
	result = ' ';

}



/* go_next: returns a win rate node pointer, no args.
  
   This function simply returns the next pointer by reference.
*/
winr_node *& winr_node::go_next()
{
	return next;
}



/* go_next_win: returns a win rate node pointer, no args

   This function simply returns the pointer to the next win
   in the list by reference.
*/
winr_node *& winr_node::go_next_win()
{
	return next_win;
}



/* set_next: nothing is returned, passed a win rate node pointer

   This function sets the nodes next pointer to the argument.
*/
void winr_node::set_next(winr_node * in)
{
	next = in;
}



/* set_next_win: nothing is returned, passed a win rate node pointer

   This function sets the nodes next win pointer to the argument.
*/
void winr_node::set_next_win(winr_node * in)
{
	next_win = in;
}



/* set_data: returns an integer indicating success/failure, is passed an int and char

   This function sets the nodes data members to the arguments passed in.
*/
int winr_node::set_data(int game, char game_result)
{
	
	if(game_result == 'w' || game_result == 'l')
	{
		game_number = game;
		result = game_result;
	}
	else
		return 0;

return 1;
}



/* display_data, returns nothing has no args.

   Simply outputs both data members to console.
*/
void winr_node::display_data()
{
	cout << "Game: " << game_number << endl;
	cout << "Result: " << result << endl << endl;
}



/* get_game_num: returns an int, has no args

   Function returns the nodes game number.
*/
int winr_node::get_game_num()
{
	return game_number;
}



/* get_game_result: returns a char, has no args.

   Function returns the nodes game result ('w' or 'l').
*/
char winr_node::get_game_result()
{
	return result;
}



// multi-threaded list constructor
win_rate::win_rate()
{
	head = NULL;
	wins = 0;
	games_played = 0;
}



// multi-threaded list copy constructor
win_rate::win_rate(const win_rate & source)
{
	copy_list(source);
}



//multi-threaded list destructor
win_rate::~win_rate()
{
	remove_all();
}



/* load_data: returns an integer indicating success/failure, has no args.

   This function opens the game_results.txt file, and adds the results of
   each game in to a multi-threaded list.
*/
int win_rate::load_data()
{
	char result; // current games result 
	int game = 1; // current game number

	ifstream results_file;

	results_file.open("game_results.txt"); //attempt to open file

	if(results_file.is_open()) // if the file is open..
	{
		while(results_file >> result) //get the next character in the file until there are no more left
		{
			insert(game, result); //insert game result and number in to list

			++game; // update game number for next game
			++games_played; //update total games played data member.

		} 	

		link_wins(head); // after list has been made, go through the list and link wins together.

	}
	else
		return 0; // file failed to open
 
	results_file.close(); // close file.

return 1;
}



/* insert: nothing is returned, is passed an int and char.

   Inserts a new node at the head of the multi-threaded list.
*/
void win_rate::insert(int game, char game_result)
{
	winr_node * temp; //temporary node pointer

	if(!head) // if the list is empty
	{
		head = new winr_node;
		head->set_data(game, game_result);		
		head->set_next(NULL);
	}
	else 
	{
		temp = new winr_node;
		temp->set_data(game, game_result);
		temp->set_next(head);
		head = temp;	
	}

}



/* display: nothing is returned, no args.

   Traverses the entire list (skips next_win pointers), and
   displays the contents of each node.
*/
void win_rate::display()
{
	winr_node * current = head; //pointer to current node

	if(current) //if there is a head
	{
		while(current) // traverse entire list
		{
			current->display_data();
			current = current->go_next();
		}
	}
}



/* remove: nothing is returned, is passed an int.

   Function to remove the node with game number matching the argument.
*/
void win_rate::remove(int game_number)
{
	winr_node * current = head; //current place in list
	winr_node * previous = NULL; // previous node in list

	if(current) //if there is a list..
	{
		while(current && current->get_game_num() != game_number) // while there is a node, and we have not found a matching node.
		{
			previous = current;
			current = current->go_next();
		}

		if(!previous) //if the node to remove is the first one
			head = head->go_next();
		else //otherwise rewire the list
			previous->set_next(current->go_next());

		delete current; //remove the current node.
	}
}



/* display_win_percentage: returns nothing, has no args.

   Calls recursive function that totals wins in the list, then
   displays the percentage of wins the player has.
*/
void win_rate::display_win_percentage()
{
	int wins = 0; // total wins

	wins = count_wins(head); // go and count the wins

	cout << "Welcome back! You've beaten this game " << (float)wins/games_played * 100 << "\% of the time.\n\n";
}
	


/* retrieve: returns an integer indicating success/failure, is passed an int and char.

   Searches the list for the game number matching the int arg, and sets the char arg
   to the result of that game.
*/
int win_rate::retrieve(int game_num, char & to_get)
{
	winr_node * current = head; //current node pointer

	if(current) //if there is a list.
	{
		while(current) // traverse list
		{
			if(current->get_game_num() == game_num) //if current node is a match..
			{
				to_get = current->get_game_result(); // set result
				return 1; //stop traversal
			}
			else //otherwise keep looking.
			{
				current = current->go_next();
			}
		}

	}
return 0; //node was not found.
}



/* remove_all: returns nothing, has no args.

   Destroys the list.
*/
void win_rate::remove_all()
{
	winr_node * temp; //temp node pointer

	if(head) //if there is a list
	{
		while(head) //while there is a list
		{
			temp = head->go_next(); //hang on to next node

			head->set_next(NULL); //remove node at head
			delete head;

			head = temp; //go to next node
		}
	}
}



/* link_wins: returns nothing, is passed a node pointer by reference.

   Traverses the multi-threaded list, keeps track of where wins are in the list
   and links them together via the next_win pointers.
*/
void win_rate::link_wins(winr_node * & start)
{
	winr_node * current = head; //current node
	winr_node * previous_win = NULL; // the last node to have a win

	int l_flag = 0; // flag to help control different situations while linking wins.

	if(current) //if there is a list
	{
		while(current) //traverse list
		{
			if(l_flag == 1 && current->get_game_result() == 'w') // if flag is set, and result is a win
			{
				if(!previous_win) //if there hasn't been a win yet.
				{
					l_flag = 0; //unflag
					previous_win = current; //set previous win to this node
				}
				else
				{
					l_flag = 0; //unflag
					previous_win->set_next_win(current); // set nodes next_win pointer
					previous_win = current; //move previous win to this node.
				}
			}

			else if(l_flag == 0 && current->get_game_result() == 'w') // if flag is not set and result is a win
			{
			
				if(!previous_win) //if there hasn't been a win yet.
				{
					l_flag = 1; //set flag
					previous_win = current; //move previous win to this node
				}
				else
				{
					l_flag = 1; //set flag
					previous_win->set_next_win(current); //set last wins next_win to this node
					previous_win = current; //move previous win here.
				}
			}	
			
			else if(current->get_game_result() == 'l') //if result is a loss
			{
				l_flag = 1; //set the flag
			}

			current = current->go_next(); // move on
		}
	}
}



/* count_wins: returns an integer, is passed a node pointer.

   recursive function that totals the number of wins in the list by
   following the next_win pointers.
*/
int win_rate::count_wins(winr_node * head)
{
	if(!head) //if head is null, get out
		return 0;
	else if(head->get_game_result() == 'l') // find the first win in the list.
		count_wins(head->go_next());
	else
		return 1 + count_wins(head->go_next_win()); //follow next_win pointers to the end, counting each one.
}



/* copy_list: returns nothing, is passed a win_rate class.

   Copies the contents of the passed in multi-threaded list,
   to this one.
*/
void win_rate::copy_list(const win_rate & source)
{
	char game_result; //current game result
	int game; //current game number

	winr_node * current = source.head; //current node in list

	while(current) //traverse list
	{
		//retrieve data members
		game = current->get_game_num(); 
		game_result = current->get_game_result();
	
		//insert node in to this list
		insert(game, game_result);

		current = current->go_next();
	}
	

}



/* save_data: returns nothing, is passed a char.

   Writes its argument to the game_result file.
*/
void win_rate::save_data(char game_result)
{
	ofstream result_file;
		
	result_file.open("game_results.txt", ios::app); //open game_results file to append to it.

	if(result_file.is_open()) //if the file opened
		result_file << game_result << '\n'; //add game_result to the end of the file.
	else
		return;

	result_file.close(); //close file.
}

