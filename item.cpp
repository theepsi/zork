#include <iostream>
#include "item.h"

Item::Item(const string& name, const string& description, bool pickable) :
	Entity(EntityType::ITEM, name, description),
	pickable(pickable) {}

Item::~Item() {

}

void Item::UseItem() {
	
}



