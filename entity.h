#ifndef _entity
#define _entity

#include <list>
#include <string>

using namespace std;

enum EntityType { CREATURE, EXIT, ROOM, ITEM, NPC, PLAYER };

class Entity {
public:
	Entity(EntityType type, const string& name, const string& description);
	virtual ~Entity();

	virtual void Update();
	virtual void Investigate();
	
	void AddEntity(Entity* ent);
	Entity* GetEntityByName(const string& item_name);

	EntityType type;
	const string name;
	const string description;
	list<Entity*> contains;

};

#endif
