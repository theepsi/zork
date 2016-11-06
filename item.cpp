#include <iostream>
#include "item.h"

Item::Item(const string& name, const string& description) :
	Entity(EntityType::ITEM, name, description) {}

Item::~Item() {

}

void Item::UseItem() {
	
}
