#include <iostream>
#include "item.h"

Item::Item(const string& name, const string& description, const string& action, bool pickable, bool canContains) :
	Entity(EntityType::ITEM, name, description),
	pickable(pickable), action(action), canContains(canContains) {}

Item::~Item() {

}

void Item::Use() {
	if (action != "")
		cout << action << "\n";
	else
		cout << "Anything special to mention about that...\n";
}



