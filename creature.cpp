#include <iostream>
#include "creature.h"

Creature::Creature(const string& name, const string& description, Room* room) :
	Entity(EntityType::CREATURE, name, description, (Entity*)room) {}

Creature::~Creature() {

}

bool Creature::Move(const string& direction) {
	//TODO: do stuff when move to another room.
	return true;
}