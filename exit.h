#ifndef _exit
#define _exit

#include <string>
#include "entity.h"

class Room;

using namespace std;

enum ExitDirection { NORTH, SOUTH, EAST, WEST };

class Exit : public Entity {
public:
	Exit(const string name, const string description, Room* origin, Room* destination);

	Room* GetDestination() {
		return (Room*)destination;
	}
	
	Room* destination;
	bool closed;
	bool locked;
	Entity* key;
};

#endif
