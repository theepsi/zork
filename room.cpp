#include <iostream>
#include "room.h"

Room::Room(const string name, const string description) :
	Entity(EntityType::ROOM, name, description, NULL) {}

void Room::Investigate() {
	cout << name << " - ";
	cout << description << "\n";

	cout << "Here you can find: \n";
	if (!contains.empty()) {
		for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
				Entity* ent = *it;
				cout << "\t" << ent->name << ": ";
				cout << ent->description << "\n";
			}
	}
	else {
		cout << "\t Nothing to see here.\n";
	}
}

void Room::AddEntity(Entity* ent) {
	contains.push_back(ent);
}