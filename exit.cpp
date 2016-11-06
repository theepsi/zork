#include <iostream>
#include "exit.h"

Exit::Exit(const string& name, const string& description, Room* origin, Room* destination, bool closed, bool locked, Item* key) :
	Entity(EntityType::EXIT, name, description),
	origin(origin), destination(destination), closed(closed), locked(locked), key(key) {

}

Exit::~Exit() {

}