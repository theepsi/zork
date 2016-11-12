#include <iostream>
#include "creature.h"
#include "room.h"
#include "exit.h"

Creature::Creature(const string& name, const string& description, Room* location) :
	Entity(EntityType::CREATURE, name, description),
	location(location) {}

Creature::~Creature() {

}

void Creature::Investigate() {
	location->Investigate();
}

bool Creature::Move(const string& direction) {
	if (location->exits.find(direction) != location->exits.end() ){
		Exit* exit = location->exits[direction];
		if (exit->closed) {
			cout << "The door is closed.\n";
			return false;
		}
		//TODO: move taking care of the keys, closed and locked doors
		location = exit->destination;
		return true;
	}
	else {
		cout << "There is no way in that direction.\n";	
		return false;
	}
}

bool Creature::OpenDoor(const string& direction) {
	if (location->exits.find(direction) != location->exits.end()) {
		//TODO take care fo keys
		Exit* exit = location->exits[direction];
		exit->closed = false;
		return true;
	}
	else {
		cout << "I cannot do that\n";
		return false;
	}
}

bool Creature::UseItem(const string& item) {
	return true;
}

void Creature::ShowInventory() {

	if (!contains.empty()) {
		cout << "Pockets: \n";
		for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
			Entity* ent = *it;
			cout << "\t" << ent->name << ": ";
			cout << ent->description << "\n";
		}
	}
	else {
		cout << "You had nothing in your pockets.\n";
	}
}

void Creature::PickUpItem(const string& item_name) {
	Entity* item = location->GetEntityByName(item_name);
	if (item != NULL) {
		location->contains.remove(item);
		contains.push_back(item);

		cout << "You pick up a " << item->name << "\n";
	}
	else {
		cout << "There is no item like that here. \n";
	}
}

void Creature::DropItem(const string& item_name) {
	Entity* item = GetEntityByName(item_name);
	if (item != NULL) {
		contains.remove(item);
		location->contains.push_back(item);

		cout << "You drop " << item->name << "\n";
	}
	else {
		cout << "There is no item like that in your pockets. \n";
	}
}

