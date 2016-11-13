#include <iostream>
#include "item.h"

Item::Item(const string& name, const string& description, const string& action, bool pickable) :
	Entity(EntityType::ITEM, name, description),
	pickable(pickable), action(action) {}

Item::~Item() {

}

void Item::UseItem() {
	if (action != "")
		cout << action << "\n";
	else
		cout << "Anything special to mention about that...\n";
}



