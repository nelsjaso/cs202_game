/* Name: Jason Nelson
   Date: 7/26/2013
   Class: CS202 Assignment: program 2

   File: character.cpp

   This file contains the implementation of the character and monster classes
 
   updated 8/6 to include operator overloading for character class
 
*/
#include "character.h"
#include "dungeon.h"


// stats constructor
stats::stats()
{
	strength = 0;
	dexterity = 0;
	intelligence = 0;
	damage = 0;
	armor = 0;
	health = 0;
	dice = 6; // six sided die
}



//stats copy constructor
stats::stats(const stats & source)
{
	strength = source.strength;
	dexterity = source.dexterity;
	intelligence = source.intelligence;
	damage = source.damage;
	armor = source.armor;
	health = source.health;
	dice = source.dice;
}



// alternate stats constructor, if you know ahead of time what the stats should be
stats::stats(int str, int dex, int intel, int dam, int arm, int hp)
{
	strength = str;
	dexterity = dex;
	intelligence = intel;
	damage = dam;
	armor = arm;
	health = hp;
	dice = 6;
	
}



//destructor
stats::~stats()
{
	strength = 0;
	dexterity = 0;
	intelligence = 0;
	damage = 0;
	armor = 0;
	health = 0;
	dice = 0;
}	



/* set_base_stats: returns nothing, and is passed 6 integers.

   The arguments define each of the 6 stats a character will have.
*/
void stats::set_base_stats(int str, int dex, int intel, int dam, int arm, int hp)
{
	strength = str;
	dexterity = dex;
	intelligence = intel;
	damage = dam;
	armor = arm;
	health = hp;
}



/* add_bonus_str: returns nothing, has no input

   This function adds a random value between 1-6 to a characters strength stat
*/
void stats::add_bonus_str()
{
	int bonus_str;

	srand(time(NULL));

	bonus_str = rand() % dice + 1;

	strength += bonus_str;
}



/* add_bonus_dex: returns nothing, has no input

   This function adds a random value between 1-6 to a characters dexterity stat
*/
void stats::add_bonus_dex()
{
	int bonus_dex;

	srand(time(NULL));

	bonus_dex = rand() % dice + 1;

	dexterity += bonus_dex;
}



/* add_bonus_int: returns nothing, has no input

   This function adds a random value between 1-6 to a characters intelligence stat
*/
void stats::add_bonus_int()
{
	int bonus_int;

	srand(time(NULL));

	bonus_int = rand() % dice + 1;

	intelligence += bonus_int;
}


/* improve_weapon: returns nothing, is passed an integer

   This function is used to change a characters damage (If they find a better weapon, for example)
*/
void stats::improve_weapon(int bonus)
{
	damage += bonus;
}



/* improve_armor: returns nothing, is passed an integer

   This function is used to change a characters armor (If they find better armor, for example)
*/
void stats::improve_armor(int bonus)
{
	armor += bonus;
}



/* change_health: returns nothing, and is passed an integer

   This function changes a characters hit points for better or worse.  Downward if they 
   take damage, upward if they heal themselves.
*/
void stats::change_health(int hp_change)
{
	health += hp_change;
}



/* display_stats: returns nothing, has no arguments.

   This function displays each of the 6 stats
*/
void stats::display_stats()
{
	cout << "Strength: " << strength << endl
	     << "Dexterity: " << dexterity << endl
	     << "Intelligence: " << intelligence << endl
             << "Damage: " << damage << endl
	     << "Armor: " << armor << endl
	     << "Health: " << health << endl << endl;
}



/* get_dex: returns an int, has no arguments

   This function just returns a characters dexterity stat,
   used when seeing who goes first in combat
*/
int stats::get_dex() const
{
	return dexterity;
}



/* get_health : returns an int, has no arguments

   This function just returns a characters current health.
*/
int stats::get_health()
{
	return health;
}


// character constructor
character::character()
{
	name = NULL;
	vocation = NULL;
	gender = NULL;
	race = NULL;

	max_response = 50;
}


//character constructor which initializes vocation, as well as its stats
character::character(char * my_vocation) : stats(5,5,5,25,25,100)
{
	name = NULL;
	gender = NULL;
	race = NULL;

	vocation = new char[strlen(my_vocation)+1];
	strcpy(vocation, my_vocation);	

	max_response = 50;
}



// character copy constructor
character::character(const character & source)
{
	if(source.name)
	{
		name = new char[strlen(source.name)+1];
		strcpy(name, source.name);

		gender = new char[strlen(source.gender)+1];
		strcpy(gender, source.gender);

		race = new char[strlen(source.race)+1];
		strcpy(race, source.race);

		vocation = new char[strlen(source.vocation)+1];
		strcpy(vocation, source.vocation);
	}	

	max_response = 50;
}



// character destructor
character::~character()
{
	if(name)
	{
		delete [] name;
		delete [] gender;
		delete [] race;
		delete [] vocation;
	}

	max_response = 0;
}



//overloaded insertion operator, can be used in place of display function.
ostream & operator<< (ostream & out, const character & ch)
{
	out << "Name: " << ch.name << endl
            << "Race: " << ch.race << endl
            << "Gender: " << ch.gender << endl
	    << "Vocation: " << ch.vocation << endl
            << endl
	    << "Strength: " << ch.strength << endl
	    << "Dexterity: " << ch.dexterity << endl
	    << "Intelligence: " << ch.intelligence << endl
	    << "Damage: " << ch.damage << endl
	    << "Armor: " << ch.armor << endl
	    << "Health: " << ch.health << endl << endl;

	return out;
}



//overloaded assignment operator.
character & character::operator = (const character & ch)
{
	if(this == &ch) // check for self assignment
		return *this;
	
	// free any dynamic memory already in use.
	if(name) 
		delete [] name;
	if(gender)
		delete [] gender;
	if(vocation)
		delete [] vocation;
	if(race)
		delete [] race;

	// copy new data in
	name = new char[strlen(ch.name)+1];
	strcpy(name, ch.name);
	gender = new char[strlen(ch.gender)+1];
	strcpy(gender, ch.gender);
	vocation = new char[strlen(ch.vocation)+1];
	race = new char[strlen(ch.race)+1];
	strcpy(race, ch.race);

	// copy stats
	this->set_base_stats(ch.strength, ch.dexterity, ch.intelligence, ch.damage, ch.armor, ch.health);

return *this;
}	



// overloaded less than operator, character as left operand, monster as right
bool character::operator < (const monster & mo)
{
	if(this->get_dex() < mo.get_dex())
		return true;
	else
		return false;
}



//overloaded less than operator, monster as left operand, character as right
bool operator < (const monster & mo, const character & ch)
{
	if(mo.get_dex() < ch.get_dex())
		return true;
	else
		return false;
}



//overloaded greater than operator, character as left operand, monster as right
bool character::operator > (const monster & mo)
{
	if(this->get_dex() > mo.get_dex())
		return true;
	else
		return false;
}



//overloaded greater than operator, monster as left operand, character as right
bool operator > (const monster & mo, const character & ch)
{
	if(mo.get_dex() > ch.get_dex())
		return true;
	else
		return false;
}



//overloaded less than or equal operator, character as left operand, monster as right
bool character::operator <= (const monster & mo)
{
	if(this->get_dex() <= mo.get_dex())
		return true;
	else
		return false;
}



//overloaded less than or equal operator, monster as left operand, character as right
bool operator <= (const monster & mo, const character & ch)
{
	if(mo.get_dex() <= ch.get_dex())
		return true;
	else
		return false;
}



//overloaded greater than or equal operator, character as left operand, monster as right
bool character::operator >= (const monster & mo)
{
	if(this->get_dex() >= mo.get_dex())
		return true;
	else
		return false;
}



//overloaded greater than or equal operator, monster as left operand, character as right
bool operator >= (const monster & mo, const character & ch)
{
	if(mo.get_dex() >= ch.get_dex())
		return true;
	else
		return false;
}


//overloaded equality operator, character as left operand, monster as right
bool character::operator == (const monster & mo)
{
	if(this->get_dex() == mo.get_dex())
		return true;
	else
		return false;
}



//overloaded equality operator, monster as left operand, character as right
bool operator == (const monster & mo, const character & ch)
{
	if(mo.get_dex() == ch.get_dex())
		return true;
	else
		return false;
}



//overloaded not equal operator, character as left operand, monster as right
bool character::operator != (const monster & mo)
{
	if(this->get_dex() != mo.get_dex())
		return true;
	else
		return false;
}



//overloaded not equal operator, monster as left operand, character as right 
bool operator != (const monster & mo, const character & ch)
{
	if(mo.get_dex() != ch.get_dex())
		return true;
	else
		return false;
}



/* create_character: returns nothing, has no arguments

   This function prompts the user for information regarding a character.
*/
void character::create_character()
{
	char temp[max_response];

	cout << "What is this characters name? ";
	cin.get(temp, max_response, '\n');
	cin.ignore(100, '\n');

	name = new char[strlen(temp)+1];
	strcpy(name, temp);

	cout << "What is this characters gender? ";
	cin.get(temp, max_response, '\n');
	cin.ignore(100, '\n');

	gender = new char[strlen(temp)+1];
	strcpy(gender, temp);

	cout << "What is this characters race? ";
	cin.get(temp, max_response, '\n');
	cin.ignore(100, '\n');

	race = new char[strlen(temp)+1];
	strcpy(race, temp);

	if(!vocation) //If the vocation hasn't already been initialzed, a new character will need one!
	{
		cout << "What is this characters vocation? ";
		cin.get(temp, max_response, '\n');
		cin.ignore(100, '\n');

		vocation = new char[strlen(temp)+1];
		strcpy(vocation, temp);
	}
}



/* display_character: returns nothing, has no arguments.

   This function displays both a characters information, and its stats
*/
void character::display_character()
{
	cout << "Name: " << name << endl
	     << "Gender: " << gender << endl
	     << "Race: " << race << endl
	     << "Vocation: " << vocation << endl << endl;

	cout << "Stats:" << endl;
	display_stats();
}



// warrior constructor, when created it initializes its vocation to warrior.
warrior::warrior() : character(const_cast<char *>("Warrior"))
{

}



//warrior destructor
warrior::~warrior()
{

}



/* introduction: returns nothing, has no arguments.

   This function tells the player some specific combat details
   about the warrior class
*/
void warrior::introduction()
{
	cout << "You are playing as Warrior!" << endl;
	cout << "Basic attack: based on your strength and damage stats" << endl;
	cout << "Special attack: 'Shield bash' uses your armor stat in place of damage." << endl;
}



/* attack: returns an int, has no arguments.

   This is the warriors attack, it returns the amount of damage
   dealt in a normal attack.
*/
int warrior::attack()
{
	int attack_damage = strength+damage;
	cout << "You swing your sword at the monster, dealing " << attack_damage << " points of damage." << endl;
	
	return attack_damage;

}



/* special_attack: returns an int, has no arguments.

   This is the warriors special attack, it returns the amount
   of damage dealt.
*/
int warrior::special_attack()
{
	int attack_damage = armor+damage;
	cout << "You slam your shield in to your enemeny, dealing " << attack_damage << " points of damage." << endl;
	
	return attack_damage;

}



// Haven't implemented this yet, but I want to give a stat bonus to the player when they descend a level in the dungeon
void warrior::level_bonus()
{

}



// thief constructor, when created it initializes its vocation to thief.
thief::thief() : character(const_cast<char *>("Thief"))
{

}


//thief destructor
thief::~thief()
{

}



/* introduction: returns nothing, has no arguments.

   This function informs the player of some specific combat
   details regarding the thief class.
*/
void thief::introduction()
{
	cout << "You are playing as a Thief!" << endl;
	cout << "Basic attack: based on your damage dexterity stats." << endl;
	cout <<"Special attack: 'Find Weakness' uses your intelligence stat to deal additional damage." << endl;
}



/* attack: returns an integer, has no arguments.

   This function returns the amount of damage dealt
   by a normal thief attack.
*/
int thief::attack()
{
	int attack_damage = dexterity+damage;
	cout << "You swing your dagger at the monster, dealing " << attack_damage << " points of damage." << endl;

	return attack_damage;

}



/* special_attack: returns an integer, has no arguments.
 
   This function returns the amount of damage dealt
   by a special thief attack.
*/
int thief::special_attack()
{
	int attack_damage = dexterity+intelligence+damage;
	cout << "You spot a weak point in your enemy, quickly jabbing your weapon in to it dealing " << attack_damage << " points of damage." << endl;

	return attack_damage;

}


// Not implemented yet.
void thief::level_bonus()
{

}



// monster constructor
monster::monster()
{
	max_response = 20;
	type = NULL;
}


// alternate monster constructor, initializes type
monster::monster(char * my_type): stats(1,1,1,5,5,60)
{
	max_response = 20;
	
	type = new char[strlen(my_type)+1];
	strcpy(type, my_type);
}


// monster copy constructor
monster::monster(const monster & source)
{
	type = new char[strlen(source.type)+1];
	strcpy(type, source.type);
}



//monster destructor
monster::~monster()
{
	if(type)
		delete [] type;
}



/* display_monster: returns nothing, has no arguments.

   This function displays the monsters type and stats
*/
void monster::display_monster()
{
	cout << "Monster type: " << type << endl;

	cout << "Monster stats:" << endl;
	display_stats();	
}



/* get_type: returns nothing, is passed a character pointer

   This function creates a string containing the monsters type.
*/
void monster::get_type(char * & my_type)
{
	my_type = new char[strlen(type)+1];
	strcpy(my_type, type);
}



// skeleton constructor
skeleton::skeleton() : monster(const_cast<char *>("Skeleton"))
{

}



// skeleton copy constructor
skeleton::skeleton(const skeleton &)
{

}


//skeleton destructor
skeleton::~skeleton()
{

}



/* greeting: returns nothing, has no arguments.

   This message is to be displayed before combat begins.
*/
void skeleton::greeting()
{
	cout << "A magical, horrifying, animated skeleton leaps toward you. It raises it's sword and seems to stare at you." << endl;
}


/* attack: returns an int, has no arguments.

   This function returns the amount of damage dealt by 
   this monsters attack.
*/
int skeleton::attack()
{
	int attack_damage = dexterity+damage;

	cout << "The skeleton swings it's sword, dealing " << attack_damage << " points of damage." <<endl;

	return attack_damage;
}


//ogre constructor
ogre::ogre() : monster(const_cast<char *>("Ogre"))
{

}


//ogre copy constructor
ogre::ogre(const ogre &)
{

}


//ogre destructor
ogre::~ogre()
{

}



/* greeting: returns nothing, has no arguments.

   This message is to be displayed before combat begins.
*/
void ogre::greeting()
{
	cout << "A huge ogre lumbers toward you, brandishing a large club." << endl;
}



/* attack: returns an int, has no arguments.

   This function returns the amount of damage dealt by 
   this monsters attack.
*/
int ogre::attack()
{
	int attack_damage = strength+damage;
	
	cout << "The ogre raises it's club above its head, slamming it down on you for " << attack_damage << " points of damage." << endl;

	return attack_damage;
}


//evil sorcerer constructor
evil_sorcerer::evil_sorcerer() : monster(const_cast<char *>("Evil Sorcerer"))
{

}


//evil sorcerer copy constructor
evil_sorcerer::evil_sorcerer(const evil_sorcerer &)
{

}


//evil sorcerer destructor
evil_sorcerer::~evil_sorcerer()
{

}



/* greeting: returns nothing, has no arguments.

   This message is to be displayed before combat begins.
*/
void evil_sorcerer::greeting()
{
	cout << "A mysterious robed figure floats in the air before you, it quietly hovers toward you." << endl;
}



/* attack: returns an int, has no arguments.

   This function returns the amount of damage dealt by 
   this monsters attack.
*/
int evil_sorcerer::attack()
{
	int attack_damage = intelligence+damage;

	cout << "The figure waves its hands around, mumbling some unintelligible words as an arc of lightning strikes you for " << attack_damage << " points of damage." << endl;
	
	return attack_damage;
}

