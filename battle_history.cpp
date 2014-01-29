/* Name: Jason Nelson
   Date: 7/26/2013
   Class: CS202 Assignment: Program 2

   File: battle_history.cpp

   This file contains the implementation of the battle_history related classes.
*/

#include "dungeon.h"
#include "battle_history.h"


// node constructor
node::node()
{
	left = NULL;
	right = NULL;

	monster_name = NULL;
}


//node copy constructor.  I may end up removing this.
node::node(const node & source)
{
	monster_name = new char[strlen(source.monster_name)+1];
	strcpy(monster_name, source.monster_name);
}


//node destructor
node::~node()
{
	if(monster_name)
		delete [] monster_name;
}



/* check_left: returns true/false, has no arguments.

   Simply checks whether or not left is pointing to anything.
*/
bool node::check_left()
{
	if(left)
		return true;
	else
		return false;
}



/* check_right: returns true/false, has no arguments.

   Simply checks whether or not right is pointing to anything.
*/
bool node::check_right()
{
	if(right)
		return true;
	else
		return false;
}



/* go_left: returns a node pointer, has no arguments

   Returns the left pointer.
*/
node *& node::go_left()
{
	return left;
}



/* go_right: returns a node pointer, has no arguments

   Returns the right pointer.
*/
node *& node::go_right()
{
	return right;
}



/* set_left: returns an integer indicating success/failure, and is passed a node pointer

   Sets the left pointer to its argument.
*/
int node::set_left(node * source)
{
	if(left != NULL)
		left = source;
	else
	{
		left = NULL;
		return 0;
	}

return 1;
}



/* set_right: returns an integer indicating success/failure, and is passed a node pointer

   Sets the right pointer to its argument.
*/
int node::set_right(node * source)
{
	if(right != NULL)
		right = source;
	else
	{
		right = NULL;
		return 0;
	}

return 1;
}



/* set_name: returns an integer indicating success/failure, is passed a char pointer

   Sets this nodes monster_name to its argument.
*/
int node::set_name(char * monst)
{
	monster_name = new char[strlen(monst)+1];
	strcpy(monster_name, monst);

	return 1;
}



/* get_name: returns an integer indicating success/failure, is passed a char pointer

   This function points its argument to monster_name (I know I know, I need to do this in a safer way ;) )
*/
int node::get_name(char * & to_get)
{
	to_get = monster_name;
}



/* compare_name: returns an integer, is passed a char pointer.

   Compares its argument to monster_name, and returns the result
   of this check.
*/
int node::compare_name(char * to_compare)
{
	return strcmp(monster_name, to_compare);
}



/* clear_name: returns an int, has no arguments

   frees this nodes monster_name.
*/
int node::clear_name()
{
	if(monster_name)
		delete [] monster_name;
return 1;
}



/* display_name: returns an int, has no arguments

   Display the name stored in this node.
*/
int node::display_name()
{
	if(monster_name)
		cout << monster_name << endl;
	else
		return 0;
return 1;
}



//battle_history constructor
battle_history::battle_history()
{
	array_size = 4;

	history = new node * [array_size];

	for(int i=0; i < array_size; ++i)
		history[i] = NULL;
}



//battle_history copy constructor
battle_history::battle_history(const battle_history & source)
{
	array_size = 4;

	history = new node * [array_size];

	for(int i=0; i < array_size; ++i)
		copy_tree(source.history[i], history[i]);
}



//battle_history destructor
battle_history::~battle_history()
{
	for(int i=0; i < array_size; ++i)
		remove_all(i);

	delete [] history;
}



/* display_history: returns an integer indicating success/failure, has no arguments

   This is a wrapper function, which calls the recursive display function for each
   tree in the structure.
*/
int battle_history::display_history()
{
	for(int i=0; i < array_size; ++i)
	{
		if(history[i])
		{
			cout << "You defeated the following monsters on floor " << i+1 << ":\n";
        		display_history(history[i]);
			cout << endl;
		}
	}

return 1;
}



/* copy: returns an integer indicating success/failure, is passed 2 battle_history's

   This is sort of a wrapper function, it copies the array of trees from a source
   battle_history to a destination battle_history
*/
int battle_history::copy(battle_history * source, battle_history * & destination)
{
	//destination = new battle_history;
	
	for(int i=0; i < array_size; ++i)
		copy_tree(source->history[i], destination->history[i]);
		
return 1;
}


/* insert: returns an integer indicating success/failure, is passed an integer and char pointer.

   inserts a node with the provided monster type, into the tree at the provided index.
*/
int battle_history::insert(int index, char * monst)
{
	return insert(history[index], monst);
}



/* remove: returns an integer indicating success/failure, is passed an integer and char pointer.

   attempts to remove a node with the provided monster type, from the tree at the provided index.
*/
int battle_history::remove(int index, char * monst)
{
	return remove(history[index], monst);
}



/* remove_all: returns an integer indicating success/failure, is passed an integer.

   destroys the entire tree at the provided index.
*/
int battle_history::remove_all(int index)
{
	return remove_all(history[index]);
}



/* search: returns an integer indicating success/failure, is passed an integer and char pointer.

   searches the tree at the provided index for the provided monster type.
*/
int battle_history::search(int index, char * to_find)
{
	search(history[index], to_find);
}



/* copy_tree: returns an integer indicating success/failure, is passed 2 node pointers.

   Copies the entire tree, from the provided source node to the destination node.
*/
int battle_history::copy_tree(node * source, node * & destination)
{
	char * temp;

	if(!source)
	{
		destination = NULL;
		return 1;
	}
	else
	{
		destination = new node;
		source->get_name(temp);
		destination->set_name(temp);		

		copy_tree(source->go_left(), destination->go_left());
		copy_tree(source->go_right(), destination->go_right());
	}
}



/* search: returns an integer indicating success/failure, is passed a node pointer and a char pointer.

   Searches the current tree for its argument.
*/
int battle_history::search(node * root, char * to_find)
{
	if(!root) 
		return 0;
	else //look for the node in question
	{
		if(root->compare_name(to_find) == 0)
			return 1;

		else if(root->compare_name(to_find) < 0)
			search(root->go_left(), to_find);

		else
			search(root->go_right(), to_find);
	}
}



/* insert: returns an integer indicating success/failure, is passed a node pointer and char pointer.

   inserts a new node in to the tree, with the provided monster name.
*/
int battle_history::insert(node * & root, char * monst)
{
	if(!root) //create the node here
	{
		root = new node;
		root->set_name(monst);
	}
	else // find the right place for the node
	{
		if(root->compare_name(monst) > 0)
		{
			insert(root->go_left(), monst);
		}
		else
		{
			insert(root->go_right(), monst);
		}
	}

return 1;
}



/* remove: returns an integer indicating success/failure, is passed a node pointer and a char pointer.

   attempts to remove a node with a name matching its argument from the provided tree.
*/
int battle_history::remove(node * & root, char * monst)
{
	node * temp; //temp node pointer
	node * prev; // holds on to previous node
	char * temp_str2; //temp string pointer

	if(!root)  
		return 0;
	

	if(root->compare_name(monst) != 0) //if this isn't the node we want, keep looking.
	{
		if(root->compare_name(monst) > 0)
			remove(root->go_left(), monst);
		else
			remove(root->go_right(), monst);

		return 0;
	}
	else
	{
		if(!root->check_left() && !root->check_right()) //if we are at a leaf
		{
			delete root;
			root = NULL;
		}
		else if(root->check_left() && !root->check_right()) //if there is a left child, but no right
		{
			delete root;
			root = root->go_left();
			
		}
		else if(root->check_right() && !root->check_left()) //if there is a right child but no left
		{
			delete root;
			root = root->go_right();
		}		
		else if(root->check_left() && root->check_right()) //if there are two children
		{
			temp = root->go_right(); //first find the in-order successor
			prev = NULL;

			while(temp->check_left())
			{
				prev = temp;
				temp->go_left();
			}

			root->clear_name(); //replace node with successor
			temp->get_name(temp_str2);
			root->set_name(temp_str2);

			//fix up the tree!
			if(prev)
				prev->set_left(temp->go_right());
			else
				root = temp->go_right();

			delete temp; //remove the stray node.
		}

	return 1;
	}
}	



/* remove_all: returns an integer indicating success/failure, is passed a node pointer.

   destroys the provided tree.
*/
int battle_history::remove_all(node * & root)
{
	if(!root)
		return 1;
	
	remove_all(root->go_left());
	remove_all(root->go_right());

	delete root;
	root = NULL;
}



/* display_history: returns an integer indicating success/failure, is passed a node pointer.

   Displays the name held in each node of the provided tree.
*/
int battle_history::display_history(node * root)
{
	if(!root)
		return 0;


	display_history(root->go_left());

	root->display_name(); // display the names in order
	
	display_history(root->go_right());

return 1;	
}
