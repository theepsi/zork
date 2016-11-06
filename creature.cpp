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
		cout << "There is no way in that direction.";	
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
		cout << "I cannot do that";
		return false;
	}
}

bool Creature::UseItem(const string& item) {
	return true;
}

