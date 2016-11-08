#ifndef _exit
#define _exit

#include <string>
#include "entity.h"

class Room;
class Item;

using namespace std;

class Exit : public Entity {
public:
	Exit(const string& name, const string& description, Room* origin, Room* destination, bool closed, bool locked, Item* key);
	~Exit();

	Room* GetDestination() {
		return (Room*)destination;
	}
	
	Room* destination;
	Room* origin;
	bool closed;
	bool locked;
	Item* key;
};

#endif
