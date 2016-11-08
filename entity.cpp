#include <iostream>
#include "entity.h"

Entity::Entity(EntityType type, const string& name, const string& description) :
	type(type), name(name), description(description) {}

Entity::~Entity() {

}

void Entity::Update() {

}

void Entity::Investigate() {
	
}

void Entity::AddEntity(Entity* ent) {

}

Entity* Entity::GetEntityByName(const string& item_name) {
	if (!contains.empty()) {
		for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
			Entity* ent = *it;
			if (ent->name == item_name) {
				return ent;
			}
		}
		return NULL;
	}
	else {
		return NULL;
	}
}
