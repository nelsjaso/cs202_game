/* Name: Jason Nelson
   Date: 7/26/2013
   Class: CS202 Assignment: Program 2

   file: battle_history.h

   This file contains the class definitions for the data structure I implemented for program 2, which
   is an array of binary search trees.
*/


// A single node in a tree
class node
{
	public:
		node(); //constructor
		node(const node &); //copy constructor
		~node(); //destructor

		node * & go_left(); // returns the left pointer
		node * & go_right(); // returns the right pointer
		int set_left(node * left); // set the left pointer
		int set_right(node * right); //set the right pointer
		bool check_left(); // check if left is pointing to something
		bool check_right(); //check if right is pointing to something


		int compare_name(char *); //compares arg to monster_name
		int set_name(char *); //set monster_name
		int get_name(char * &); //get monster_name
		int display_name(); // output name
		int clear_name(); 

	protected:
		node * left;
		node * right;

		char * monster_name;
};

// Array of bsts
class battle_history 
{
	public:
		battle_history(); //constructor
		battle_history(const battle_history &); //copy constructor
		~battle_history(); //destructor
		
		// wrapper functions
		int insert(int, char *); //insert a node into a tree
		int remove(int, char *); //remove a node from a tree
		int search(int, char *); //search a tree for a name
		int remove_all(int); //destroy a tree
		int display_history(); //display contents of all trees
		int copy(battle_history * source, battle_history * & destination); //copy this structure 

	protected:
		node ** history;
		int array_size;

		// recursive functions
		int copy_tree(node *, node * &); 
		int insert(node * &, char *); 
		int remove(node * &, char *); 
		int search(node *, char *); 
		int remove_all(node * &); 
		int display_history(node *); 
};
