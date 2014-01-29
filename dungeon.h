/* Name: Jason Nelson
   Date: 7/26/2013
   Class: CS202 Assignment: Program 2

   File: dungeon.h

   This file contains the class definitions related to the games
   dungeon.
*/


#include <iostream> // general i/o
#include <cstring> // used for strcpy, strlen
#include <time.h> // used to get a seed for the random number generator
#include <stdlib.h> // used for its random number generator
#include <fstream> // file i/o

using namespace std;

//Each room contains a piece of the story
class story_piece
{
	public:
		story_piece(); //constructor
		story_piece(const story_piece &); //copy constructor
		~story_piece(); //destructor
		void display_story(); //Show this bit of the story
		void set_story(char *); // Set this bit of the story
		void get_story(char *); // retrieve this bit of the story

	protected:
		char * story;

	private:
		int max_size; // max length of a story piece
};



//A dungeon contains many rooms, inherits from story_piece
class room : public story_piece
{
	public:
		room(); //constructor
		room(const room &); //copy constructor
		~room(); //destructor
		int get_next_room(room * & next); //get the next room
		int set_next_room(room * next); //set the next room

	protected:
		room * next_room;		
};



// An adjacency list that represents the dungeon, contains an array of room pointers
class dungeon
{
	public:
		dungeon(); //constructor
		dungeon(const dungeon &); //copy constructor
		~dungeon(); //destructor
		
		int insert(int, char *); // insert a story piece in to a new room in the dungeon
		int load_dungeon(); // construct the dungeon from a file
		int remove_all(); // remove all rooms from the dungeon
		int display(); // display the stories from each room in the dungeon
		int display_next_room();
		//int go_to_next_room()?
		int get_floor();

		
	protected:
		room ** list;
		room * current_room;

	private:
		int num_floors; // size of list
		int current_floor; //what floor are we on currently?
		int num_rooms;
		int rooms_visited;
};
