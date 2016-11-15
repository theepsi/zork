#include <iostream>
#include "entity.h"

Entity::Entity(EntityType type, const string& name, const string& description) :
	type(type), name(name), description(description) {}

Entity::~Entity() {

}

void Entity::Update() {

}

void Entity::Investigate() {
	cout << name << ":\t" << description << "\n";
	if (!contains.empty()) {
		cout << "\nHere you can find: \n";
		for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
			Entity* ent = *it;
			cout << "\t" << ent->name << ":\t";
			cout << ent->description << "\n";
		}
	}
}

void Entity::AddEntity(Entity* ent) {
	contains.push_back(ent);
}

Entity* Entity::GetEntityByName(const string& item_name) {
	for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
		if ((*it)->name == item_name) {
			return *it;
		}
	}
	return NULL;
}

void Entity::DeleteEntityByName(const string& item_name) {
	Entity* ent = GetEntityByName(item_name);
	if (ent != NULL) {
		contains.remove(ent);
	}
}
