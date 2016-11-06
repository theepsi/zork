#ifndef _room
#define _room

#include <map>
#include "entity.h"

class Exit;

class Room : public Entity {
public:
	Room(const string& name, const string& description);
	~Room();
	void Investigate();
	void AddEntity(Entity* ent);
	Exit* GetExit(const string& direction);
	void AddExit(Exit* exit, const string& placement);

	map<string, Exit*> exits;
};

#endif

