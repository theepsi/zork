#ifndef _creature
#define _creature

#include "entity.h"

class Room;

class Creature : public Entity {
public:
	Creature(const string& name, const string& description, Room* location);
	~Creature();
	void Investigate();
	virtual bool Move(const string& direction);
	bool OpenDoor(const string& direction);
	bool UseItem(const string& item);
	void ShowInventory();
	void PickUpItem(const string& item_name);
	void DropItem(const string& item_name);

	Room* location;
};

#endif

