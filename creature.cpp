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
		//TODO: move taking care of the keys, closed and locked doors
		location = exit->destination;
		return true;
	}
	else {
		return false;
	}
}

