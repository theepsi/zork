#ifndef _item
#define _item

#include "entity.h"

class Item : public Entity {
public:
	Item(const string name, const string description);
	
	void UseItem();
};

#endif

