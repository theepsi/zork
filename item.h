#ifndef _item
#define _item

#include "entity.h"

class Item : public Entity {
public:
	Item(const string& name, const string& description, const string& action, bool pickable, bool canContains);
	~Item();
	void Use();

	bool pickable;
	bool canContains;
	const string action;
};

#endif

