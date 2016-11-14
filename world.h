#ifndef _world
#define _world

#include <string>
#include <list>
#include "room.h"

using namespace std;

class Entity;
class Creature;
class Item;
class Vat;

class World {
public:
	World();
	~World();
	bool Interaction(const string& input);

	list<Room*> rooms;
	Creature* player;

	Item* wckey_instance;
	Item* stkey_instance;
	Item* winkey_instance;
	bool wckey_dropped = false;
	bool cookers_working = false;
	bool water_puzzle_complete = false;

	map<string, Vat*> vat_game;
	map<Item*, list<Item*>> combinables;
	map<string, list<Item*>> combine_to;

};

#endif
