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

void Entity::DeleteEntityByName(const string& item_name) {
	if (!contains.empty()) {
		for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
			Entity* ent = *it;
			if (ent->name == item_name) {
				contains.remove(ent);
				break;
			}
		}
	}
}
