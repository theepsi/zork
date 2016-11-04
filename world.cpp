#include <iostream>
#include "entity.h"
#include "creature.h"
#include "world.h"
#include "item.h"

World::World() {
	//GAME Entities...


	//ROOMS

	Room* living_room = new Room("Living Room", "The living room of the house.");

	//ITEMS

	Item* book = new Item("Book", "Description of the game.");
	Item* letter = new Item("Letter", "Welcome to the game letter.");

	living_room->AddEntity(book);
	living_room->AddEntity(letter);

	// Add rooms to the game.
	rooms.push_back(living_room);


	//PLAYER
	player = new Creature("Player", "The person who is trapped inside the house.", living_room);

}

bool World::Interaction(const string& input) {

	bool response = true;

	if (input == "investigate") {
		player->parent->Investigate();
	}
	else if (input == "hi") {
		cout << "There is nobody here, you are alone... \n";
	}
	else {
		response = false;
	}

	return response;
}