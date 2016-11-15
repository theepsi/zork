#ifndef _vat
#define _vat

#include "entity.h"
#include "item.h"

class Vat : public Item {
public:
	Vat(const string& name, const string& description, int capacity, int filled);
	~Vat();
	void MoveWater(Vat* dest);

	int filled;
	int capacity;
	bool IsFull() {
		return filled == capacity;
	}
	int GetFreeSpace() {
		return capacity - filled;
	}
};

#endif

