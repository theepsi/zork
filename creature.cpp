#include <iostream>
#include "creature.h"
#include "room.h"
#include "item.h"
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
		location = exit->destination;
		return true;
	}
	else {
		cout << "There is no way in that direction.\n";	
		return false;
	}
}

