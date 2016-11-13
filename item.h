#ifndef _item
#define _item

#include "entity.h"

class Item : public Entity {
public:
	Item(const string& name, const string& description, bool pickable);
	~Item();
	void UseItem();
	void OpenVault(const string& code);

	bool pickable;
};

#endif

