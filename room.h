#ifndef _room
#define _room

#include "entity.h"

class Room : public Entity {
public:
	Room(const string name, const string description);
	void Investigate();

};

#endif

