/* Name: Jason Nelson
   Date: 7/29/2013
   Class: CS202 Assignment: Program 3

   File: win_rate.h

   This file contains the class definitions for a data structure which
   tracks how often the player has won the game, it does this via a
   multi-threaded list which reads from and writes to an external file.
*/



// multi-threaded list node
class winr_node
{
	public:
		winr_node(); //constructor
		~winr_node(); //destructor

		winr_node * & go_next(); // return the next node
		winr_node * & go_next_win(); // return the next win
		void set_next(winr_node *); // set next pointer
		void set_next_win(winr_node *); // set next win pointer
		int set_data(int, char); // set node data
		char get_game_result(); //retrieve game result
		int get_game_num(); // retrieve game number
		void display_data(); // output game result and number

	protected:
		winr_node * next; // next node in the list
		winr_node * next_win; // next win in the list

		int game_number; 
		char result; // win or loss
};



//multi-threaded list
class win_rate
{
	public:
		win_rate(); //constructor
		win_rate(const win_rate &); //copy constructor
		~win_rate(); //destructor

		int load_data(); //read from file, build list
		void insert(int, char); // add to list 
		void remove(int); //remove by game number
		void display(); //display game number + result of each game
		void display_win_percentage(); // total wins, calculate win percentage, display results 
		int retrieve(int, char &); //retrieve by game number
		void remove_all(); //destroy list    
		void copy_list(const win_rate &); //copy list

		void save_data(char); // append game result to file

	protected:
		winr_node * head;
		int wins;
		int games_played;
		
		void link_wins(winr_node * &); // go through list, link wins together
		int count_wins(winr_node *); // recursive function that totals wins in list

};
