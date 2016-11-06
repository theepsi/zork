#include <iostream>
#include "entity.h"

Entity::Entity(EntityType type, const string& name, const string& description) :
	type(type), name(name), description(description) {}

Entity::~Entity() {

}

void Entity::Update() {

}

void Entity::Investigate() {
	
}

void Entity::AddEntity(Entity* ent) {

}
