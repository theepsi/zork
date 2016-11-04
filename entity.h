#ifndef _entity
#define _entity

#include <list>
#include <string>

using namespace std;

enum EntityType { CREATURE, EXIT, ROOM, ITEM, NPC, PLAYER };

class Entity {
public:
	Entity(EntityType type, const string name, const string description, Entity* parent);
	virtual void Update();
	virtual void Investigate();
	virtual void AddEntity(Entity* ent);

	EntityType type;
	const string name;
	const string description;
	Entity* parent;
	list<Entity*> contains;

};

#endif
