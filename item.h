#ifndef _item
#define _item

#include "entity.h"

class Item : public Entity {
public:
	Item(const string& name, const string& description, const string& action, bool pickable);
	~Item();
	void UseItem();

	bool pickable;
	const string action;
};

#endif

