#include <iostream>
#include "vat.h"

Vat::Vat(const string& name, const string& description, int capacity, int filled) :
	Item(name, description, "", false, false),
	filled(filled), capacity(capacity) {}

Vat::~Vat() {

}

void Vat::MoveWater(Vat* dest) {
	if (!dest->IsFull()) {
		if (filled >= dest->GetFreeSpace()) {
			filled = filled - dest->GetFreeSpace();
			dest->filled = dest->capacity;
		}
		else {
			dest->filled = dest->filled + filled;
			filled = 0;	
		}
	}
	else {
		cout << "Destination vat is full.\n";
	}
}