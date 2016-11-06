#include <iostream>
#include "entity.h"
#include "creature.h"
#include "world.h"
#include "item.h"
#include "exit.h"

World::World() {
	//GAME Entities...


	//ROOMS

	Room* living_room = new Room("Living Room", "The living room of the house.");
	Room* bath_room = new Room("Bath Room", "This is the bath room.");
	Room* storage_room = new Room("Storage Room", "Here you can see a lot of things.");
	Room* kitchen = new Room("Kitchen", "An Old Kitchen with some dishes.");
	Room* big_room = new Room("Big Room", "A very clean room, with a big bed.");
	Room* win_room = new Room("Win!", "You win the game, you scape from there!");

	//ITEMS

	Item* book = new Item("Book", "Description of the game.");
	Item* letter = new Item("Letter", "Welcome to the game letter.");

	living_room->AddEntity(book);
	living_room->AddEntity(letter);

	// Add rooms to the game.
	rooms.push_back(living_room);


	//EXITS

	Exit* living_to_bathroom = new Exit("To Bathroom", "", living_room, bath_room, true, true, NULL);
	Exit* living_to_win = new Exit("To Win", "", living_room, win_room, true, true, NULL);
	Exit* living_to_bigroom = new Exit("To Big room", "", living_room, big_room, true, false, NULL);
	Exit* living_to_kitchen = new Exit("To Kitchen", "", living_room, kitchen, false, false, NULL);

	Exit* bathroom_to_livingroom = new Exit("To Living room", "", bath_room, living_room, true, false, NULL);
	Exit* kitchen_to_livingroom = new Exit("To Living room", "", kitchen, living_room, false, false, NULL);
	Exit* bigroom_to_livingroom = new Exit("To Living room", "", big_room, living_room, true, false, NULL);

	Exit* kitchen_to_storage = new Exit("To Storage room", "", kitchen, storage_room, true, true, NULL);
	Exit* storage_to_kitchen = new Exit("To Storage room", "", storage_room, kitchen, true, false, NULL);

	//TODO: Create Keys to open doors.
	

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