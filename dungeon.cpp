/* Name: Jason Nelson
   Date: 7/26/2013
   Class: CS202 Assignment: program 2

   File: dungeon.cpp

   This file contains the implementation of the dungeon related classes

   Updated 8/6 to fix memory leaks
*/

#include "dungeon.h"



// story_piece constructor
story_piece::story_piece()
{
	max_size = 100;
	story = NULL;
}


// story_piece copy constructor
story_piece::story_piece(const story_piece & source)
{
	if(source.story)
	{
		story = new char[strlen(source.story)+1];
		strcpy(story, source.story);
	}
}



//story_piece destructor
story_piece::~story_piece()
{
	if(story)
		delete [] story;
}



/* display_story: returns nothing, no arguments

   Displays contained story piece
*/
void story_piece::display_story()
{
	cout << endl << story << endl << endl;
}



/* set_story: returns nothing, is passed a character array.

   This function copies its argument in to its story.
*/
void story_piece::set_story(char * source)
{
	story = new char[strlen(source)+1];
	strcpy(story, source);
}



/* get_story: returns nothing, is passed a character array

   This function allows the story piece to be retrieved
*/
void story_piece::get_story(char * to_get)
{
	to_get = story;
}



//room constructor
room::room()
{
	next_room = NULL;
}


//room copy constructor
room::room(const room & source)
{
	if(source.next_room)
		next_room = source.next_room;
	else
		next_room = NULL;
}



//room destructor
room::~room()
{
	next_room = NULL;
}



/* get_next_room: returns an integer indicating success/failure, is passed a room pointer

   This function points its argument at the next room in the list
*/
int room::get_next_room(room * & next)
{
	if(next_room != NULL)
		next = next_room;
	else
	{
		next = NULL;
		return 0;
	}

return 1;
}



/* set_next_room: returns an integer indicating success/failure, is passed a room pointer

   This function sets the next room to its argument
*/
int room::set_next_room(room * next)
{
	if(next != NULL)
		next_room = next;
	else
	{
		next_room = NULL;
		return 0;
	}

return 1;
}



//dungeon constructor, creates adjacency list
dungeon::dungeon()
{
	num_floors = 4;
	current_floor = 0;
	num_rooms = 0;
	rooms_visited = 0;

	current_room = NULL;

	list = new room * [num_floors];
	
	for(int i=0; i < num_floors; ++i)
		list[i] = NULL;
}



//dungeon copy constructor
dungeon::dungeon(const dungeon & source)
{
	room * current;
	room * temp;
	char * story;

	current_room = source.current_room;

	for(int i=0; i < num_floors; ++i)
	{
		if(source.list[i]) //visit each floor
		{
			current = list[i];

			while(current) // visit each room on the current floor
			{
				source.list[i]->get_story(story); // retrieve story piece
				insert(i, story); //insert room in to new dungeon
				
				current->get_next_room(temp);
				current = temp;
			}
		}
	}


}



// dungeon destructor
dungeon::~dungeon()
{
	current_room = NULL;
	remove_all();
	delete [] list;

}



/* insert: returns an integer indicating success/failure, is passed an integer, and a character array

   This function creates a new room after the last room on the floor indicated by its integer argument, and then
   places that rooms story piece within the room.
*/
int dungeon::insert(int index, char * story)
{
	room * current;
	room * temp;

	if(!list[index]) //If there are no rooms on this floor
	{
		list[index] = new room;
		list[index]->set_story(story);
	}
	else //otherwise add at the end of the list
	{
		current = list[index];

		while(current->get_next_room(temp))
			current = temp;	

		temp = new room;
		temp->set_story(story);
		current->set_next_room(temp);
	}

	++num_rooms;

return 1;
}



/* load_dungeon: returns an integer indicating success/failure, has no arguments.

   This function reads through an external text file, and constructs the dungeon
   our characters will adventure through.
*/
int dungeon::load_dungeon()
{
	int floor_index;
	ifstream dungeon_file;
	char temp[100];
	room * current;	

	dungeon_file.open("dungeon.txt"); //open file
	
	if(dungeon_file.is_open()) //if successful..
	{
		while(dungeon_file.getline(temp, 100)) //read the first line
		{ 
			floor_index = temp[0] - '0'; // the first character on the line is a number that tells us which floor this room is on.
					             // subtracting '0' from this value translates it from the ascii value for that character to the correct number
			temp[0] = ' '; // get rid of the floor number before inserting the story in to the room
			insert(floor_index, temp);
		}
	}
	else
		return 0; //file failed to open

	dungeon_file.close(); //close the file
return 1;	
}



/* remove_all: returns an integer indicating success/failure, has no arguments.

   This function visits each floor of the dungeon, and destroys each room.
*/
int dungeon::remove_all()
{
	room * temp;

	for(int i=0; i < num_floors; ++i)
	{
		if(list[i])
		{
			//delete list[i];
			while(list[i])
			{
				list[i]->get_next_room(temp);
				delete list[i];
				list[i] = temp;
			}	
			
			list[i] = NULL;
		}
	}

return 1;
}



/* display: returns an integer indicating success/failure, has no arguments

   This function visits each room, on each floor, and displays the story piece for each.
*/
int dungeon::display()
{
	room * current;
	room * temp;

	for(int i=0; i < num_floors; ++i)
	{
		if(list[i])
		{
			current = list[i];

			while(current)
			{
				current->display_story();				

				current->get_next_room(temp);
				current = temp;
			}
		}
	}

return 1;	
}



/* display_next_room has no arguments and returns an int which indicates
   success or failure.

   This function will output the story contained in the next room in the
   dungeon each time it is called.
*/
int dungeon::display_next_room()
{
	room * temp; // temporary room pointer

	if(rooms_visited == num_rooms) //if all the rooms have been visited, return failure
		return 0;

	if(list[current_floor]) //if there is something on the current floor
	{
		if(!current_room) // if this is the first room on a floor
		{
			current_room = list[current_floor];
			current_room->display_story();
			++rooms_visited;
		}
		else if(current_room->get_next_room(temp)) // otherwise go to the next room on the floor
		{
			current_room = temp;
			current_room->display_story();
			++rooms_visited;
		}
		else // otherwise, go down to the next floor, and try again.
		{
			current_room = NULL;
			++current_floor;
			display_next_room();
		}
			
	}
	else // If there were no rooms on this floor, return failure.
		return 0;
return 1;
}



// get floor has no arguments and simply returns the dungeons current floor
int dungeon::get_floor()
{
	return current_floor;
}

