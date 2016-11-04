#ifndef _world
#define _world

#include <string>
#include <list>
#include "room.h"

using namespace std;

class Entity;
class Creature;

class World {
public:
	World();
	bool Interaction(const string& input);

	list<Room*> rooms;
	Creature* player;

};

#endif
