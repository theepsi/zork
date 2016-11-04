#include <iostream>
#include "entity.h"

Entity::Entity(EntityType type, const string name, const string description, Entity* parent = NULL) :
	type(type), name(name), description(description), parent(parent) {}

void Entity::Update() {

}

void Entity::Investigate() {
	
}

void Entity::AddEntity() {

}
