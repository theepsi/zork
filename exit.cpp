#include <iostream>
#include "exit.h"

Exit::Exit(const string name, const string description, Room* origin, Room* destination) :
	Entity(EntityType::EXIT, name, description, (Entity*)origin),
	destination(destination), closed(false), locked(false), key(NULL) {

}
