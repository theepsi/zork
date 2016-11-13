#ifndef _world
#define _world

#include <string>
#include <list>
#include "room.h"

using namespace std;

class Entity;
class Creature;
class Item;

class World {
public:
	World();
	~World();
	bool Interaction(const string& input);

	list<Room*> rooms;
	Creature* player;

	Item* wckey_instance;
	bool wckey_dropped = false;

	map<Item*, list<Item*>> combinables;
	map<string, list<Item*>> combine_to;

};

#endif
