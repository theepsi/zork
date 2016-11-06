#ifndef _creature
#define _creature

#include "entity.h"

class Room;

class Creature : public Entity {
public:
	Creature(const string& name, const string& description, Room* location);
	~Creature();
	virtual bool Move(const string& direction);

	Room* GetRoom() {
		return (Room*)parent;
	}
};

#endif

