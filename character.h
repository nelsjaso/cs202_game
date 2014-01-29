/* Name: Jason Nelson
   Date: 7/26/2013
   Class: cs202 Assignment: Program 2

   File: character.h

   This file contains the class defintions related to an individual
   character, and an individual monster for my game.
*/

#include <iostream>
using namespace std;

//An individual characters stats
class stats
{
	public:
		stats(); //constructor
		stats(const stats &); //copy constructor
		stats(int, int, int, int, int, int); //constructor that initializes all the stats
		~stats(); //destructor
		void set_base_stats(int, int, int, int, int, int); // set each stat
		void add_bonus_str(); // add a random number 1-6 to str
		void add_bonus_dex(); // add a random number 1-6 to dex
		void add_bonus_int(); // add a random number 1-6 to int
		void improve_weapon(int); // change the damage stat
		void improve_armor(int); // change the armor stat
		void change_health(int); // change the health stat
		void display_stats(); // display all stat values
		
		int get_dex() const;
		int get_health();


	protected:
		int strength; // improves warrior damage, helps warriors break locked things open
		int dexterity; // acts like initiative, improves thief damage, helps thieves be more sneaky
		int intelligence; // used when checking for traps
		int damage; // how hard do you hit?
		int armor; // reduces incoming damage
		int health; // a characters total hit points

	private:
		int dice; //how many sides are on the dice?
};


//A monster, inherits from stats
class monster : public stats
{
	public:
		monster(char *); //initializes type
		monster(const monster &); //copy constructor
		~monster(); //destructor
		
		//void create_monster();
		void display_monster(); //display monster info + stats
		void get_type(char * &); // get the monsters type
		//void death();

		virtual int attack()=0;		
		virtual void greeting()=0; // monsters greeting before you fight it
			
	protected:
		monster(); //constructor
		char * type;

	private:
		int max_response;
};

// A character, inherits from stats
class character : public stats
{
	public:
		character(char *); //constructor that initializes vocation
		character(const character &); //copy constructor
		~character(); //destructor


		//overloaded operators: <<, =, <, >, <=, >=, ==, !=

		friend ostream & operator << (ostream & out, const character & ch);
		character & operator = (const character &);
		bool operator < (const monster &);
		friend bool operator < (const monster &, const character &);
		bool operator > (const monster &);
		friend bool operator > (const monster &, const character &);
		bool operator <= (const monster &);
		friend bool operator <= (const monster &, const character &);
		bool operator >= (const monster &);
		friend bool operator >= (const monster &, const character &);
		bool operator == (const monster &);
		friend bool operator == (const monster &, const character &);
		bool operator != (const monster &);
		friend bool operator != (const monster &, const character &);


		
		void create_character(); //make a new character
		void display_character(); //display character info + stats	
		//void explore();
		//void death();	
		//void examine();

		virtual void introduction()=0; //explains details of chosen class
		virtual int attack()=0;		
		virtual int special_attack()=0;
		//virtual void special_ability()=0;
		virtual void level_bonus()=0;	

	protected:
		character(); //constructor
		char * name;
		char * vocation;
		char * gender;
		char * race;
	
	private:
		int max_response; //used to size temporary arrays

};




//A specialty character class, inherits from character
class warrior : public character
{
	public:
		warrior(); //constructor
		warrior(const warrior &); //copy constructor
		~warrior(); //destructor

		void introduction();
		int attack();
		int special_attack(); //shield bash
		//void special_ability();
		void level_bonus();

	protected:

};



//A specialty character class, inherits from character
class thief : public character
{
	public:
		thief(); //constructor
		thief(const thief &); //copy constructor
		~thief(); //destructor

		void introduction();
		int attack();
		int special_attack(); //find weakness
		//void special_ability();
		void level_bonus();

	protected:
};



//A specialty monster class, inherits from monster
class skeleton : public monster
{
	public:
		skeleton(); //constructor
		skeleton(const skeleton &); //copy constructor
		~skeleton(); //destructor

		void greeting();
		int attack();
 
	protected:
};



//A specialty monster class, inherits from monster
class ogre : public monster
{
	public:
		ogre(); //constructor
		ogre(const ogre &); //copy constructor
		~ogre(); //destructor
	
		void greeting();
		int attack();

	protected:
	
};



//A specialty monster class, inherits from monster
class evil_sorcerer : public monster
{
	public:
		evil_sorcerer(); //constructor
		evil_sorcerer(const evil_sorcerer &); //copy constructor
		~evil_sorcerer(); //destructor

		void greeting();
		int attack();

	protected:

};
