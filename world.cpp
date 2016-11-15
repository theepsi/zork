#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "entity.h"
#include "player.h"
#include "world.h"
#include "item.h"
#include "exit.h"
#include "vault.h"
#include "vat.h"

World::World() {
	//GAME Entities...
	
	//ROOMS

	Room* living_room = new Room("Living Room", "The living room of the house.");
	Room* big_room = new Room("Bedroom", "A very clean room, with a big bed.");
	Room* bathroom = new Room("Bathroom", "This is the bath room.");
	Room* kitchen = new Room("Kitchen", "An old kitchen with some dishes.");
	Room* storage_room = new Room("Storage Room", "Here you can see a lot of things.");
	Room* win_room = new Room("Exit", "You win the game, you scaped the room!");

	//END ROOMS

	//KEYS
	Item* bedroom_key = new Item("bkey", "The key of the bedroom.", "You can use this key with the south door of the living room.", true);
	Item* bathroom_key = new Item("wckey", "The key of the bathroom.", "You can use this key with the west door of the living room.", true);
	Item* storage_key = new Item("stkey", "The key of the store room.", "You can use this key with the east door of the kitchen room.", true);
	Item* win_key = new Item("wkey", "This key leads you to the exit.", "You can use this key with the north door of the living room.", true);

	//Save instances (circumstance-appear keys)
	wckey_instance = bathroom_key;
	stkey_instance = storage_key;
	winkey_instance = win_key;

	//END KEYS

	//ITEMS

	//Living room items
	Item* book = new Item("book", "Description of the game.", "TODO", false);
	Item* letter = new Item("letter", "Welcome to the game letter.", "TODO", true);
	Item* clock = new Item("clock", "The digital clock is stuck.", "It marks 02:27 p.m.", false);
	Item* picture = new Item("picture", "A bad imitation of the Van Gogh picture \"Bedroom in Arles\", the bedding is green...", "In the original picture the bedding is red.", false);
	Vault* security_box = new Vault("security_box", "It is a small security box. Above the keyboard it says \"24 hours\".", "1427");
	Item* bookcase = new Item("bookcase", "There are a lot of books but there is one that stands out above the others.", "", false);
	Item* fake_book = new Item("fake_book", "This book is fake, it seems to have something inside.", "", false);
	Item* cardboard = new Item("cardboard", "A piece of cardboard that contains some random letters in random positions...", "* <- *    K ** E\n* -> F    H <- *\n* ** *    * -> L\n* ** Z    R <- *\nJ ** S    * ** W", true);
	
	security_box->AddEntity(bedroom_key);
	picture->AddEntity(security_box);
	fake_book->AddEntity(cardboard);
	bookcase->AddEntity(fake_book);

	living_room->AddEntity(book);
	living_room->AddEntity(letter);
	living_room->AddEntity(clock);
	living_room->AddEntity(picture);
	living_room->AddEntity(bookcase);

	//Big room items
	Item* blackboard = new Item("blackboard", "A blackboard on the wall. Read it to more details.", "BXPW WOK ZDWWGKJJ", false);
	Item* desktop = new Item("desktop", "A very clean and organized desktop.", "", false);
	Item* perforated_envelope = new Item("perforated_envelope", "A perforated envelope that contains some random letters in random positions...", "A    D      ->  \nP              O\nX -> I    B     \nM <-           G\n  ->      T <-  ", true);
	Item* mattress = new Item("mattress", "A comfortable mattress.", "There is no time to take a nap...", false);
	Item* cushion_red = new Item("cushion_red", "A red cushion.", "There is something inside this cushion...", false);
	Item* cushion_green = new Item("cushion_green", "A green cushion.", "", false);
	Item* cushion_blue = new Item("cushion_blue", "A blue cushion.", "", false);
	Item* trigger = new Item("trigger", "It is like a piece of a lighter.", "It seems like it needs more pieces to work.", true);

	desktop->AddEntity(perforated_envelope);
	cushion_red->AddEntity(trigger);
	mattress->AddEntity(cushion_red);
	mattress->AddEntity(cushion_green);
	mattress->AddEntity(cushion_blue);

	big_room->AddEntity(blackboard);
	big_room->AddEntity(desktop);
	big_room->AddEntity(mattress);

	//Bathroom items
	Item* cabinet = new Item("cabinet", "A little cabinet with a mirror.", "", false);
	Item* container = new Item("container", "It is a small container filled up with flamnable fluid.", "", true);

	cabinet->AddEntity(container);

	bathroom->AddEntity(cabinet);

	//Kitchen items
	Item* cookers = new Item("cookers", "You can burn or melt things with this, but you need a flame first.", "You need a lighter to turn on the cookers.", true);
	Item* fridge = new Item("fridge", "An old fridge.", "", false);
	Item* freezer = new Item("freezer", "A freezer inside the fridge.", "", false);
	Item* ice_cube = new Item("ice_cube", "A very solid and strong ice cube with something inside.", "", true);

	freezer->AddEntity(ice_cube);
	fridge->AddEntity(freezer);

	kitchen->AddEntity(cookers);
	kitchen->AddEntity(fridge);

	//Storage room items
	Item* letter_game = new Item("instructions", "Instructions for the water puzzle.", "You must fill with 8 liters of water both 16 and 9 liter vats, once you accomplish that, the key to the victory will be revealed to you.", false);
	Vat* water_vat_16 = new Vat("a-vat: 16L", "A vat with 16 liters of capacity.", 16, 16);
	Vat* water_vat_9 = new Vat("b-vat: 9L", "A vat with 9 liters of capacity.", 9, 0);
	Vat* water_vat_7 = new Vat("c-vat: 7L", "A vat with 7 liters of capacity.", 7, 0);

	vat_game["a"] = water_vat_16;
	vat_game["b"] = water_vat_9;
	vat_game["c"] = water_vat_7;

	storage_room->AddEntity(letter_game);
	storage_room->AddEntity(water_vat_16);
	storage_room->AddEntity(water_vat_9);
	storage_room->AddEntity(water_vat_7);
	
	//END ITEMS

	//COMBINATIONS

	//Dictionary = cardboard + perforated_envelope
	Item* result_dictionary = new Item("dictionary", "The result of combining the cardboard and the perforated envelope.", "A <- D    K -> E\nP -> F    H <- O\nX -> I    B -> L\nM <- Z    R <- G\nJ -> S    T <- W", true);

	list<Item*> cardbord_to;
	cardbord_to.push_back(result_dictionary);
	combine_to.insert(pair<string, list<Item*>>(cardboard->name, cardbord_to));

	list<Item*> penvelop_to;
	penvelop_to.push_back(result_dictionary);
	combine_to.insert(pair<string, list<Item*>>(perforated_envelope->name, penvelop_to));

	list<Item*> result_dictionary_list;
	result_dictionary_list.push_back(cardboard);
	result_dictionary_list.push_back(perforated_envelope);
	combinables.insert(pair<Item*, list<Item*>>(result_dictionary, result_dictionary_list));

	//Lighter = trigger + container

	Item* result_lighter = new Item("lighter", "It is usefull to start a flame.", "Maybe you can use it on a kitchen.", true);

	list<Item*> trigger_to;
	trigger_to.push_back(result_lighter);
	combine_to.insert(pair<string, list<Item*>>(trigger->name, trigger_to));

	list<Item*> container_to;
	container_to.push_back(result_lighter);
	combine_to.insert(pair<string, list<Item*>>(container->name, container_to));

	list<Item*> result_lighter_list;
	result_lighter_list.push_back(trigger);
	result_lighter_list.push_back(container);
	combinables.insert(pair<Item*, list<Item*>>(result_lighter, result_lighter_list));

	//END COMBINATIONS

	//EXITS

	Exit* living_to_bathroom = new Exit("A wooden door.", "", living_room, bathroom, true, true, bathroom_key);
	Exit* living_to_win = new Exit("A very heavy door.", "", living_room, win_room, true, true, win_key);
	Exit* living_to_bigroom = new Exit("A normal door.", "", living_room, big_room, true, true, bedroom_key);
	Exit* living_to_kitchen = new Exit("It seems like a kitchen.", "", living_room, kitchen, false, false, NULL);

	living_room->AddExit(living_to_bathroom, "west");
	living_room->AddExit(living_to_win, "north");
	living_room->AddExit(living_to_bigroom, "south");
	living_room->AddExit(living_to_kitchen, "east");

	Exit* bathroom_to_livingroom = new Exit("To the living room.", "", bathroom, living_room, false, false, NULL);
	Exit* kitchen_to_livingroom = new Exit("To the living room.", "", kitchen, living_room, false, false, NULL);
	Exit* bigroom_to_livingroom = new Exit("To the living room.", "", big_room, living_room, false, false, NULL);

	bathroom->AddExit(bathroom_to_livingroom, "east");
	kitchen->AddExit(kitchen_to_livingroom, "west");
	big_room->AddExit(bigroom_to_livingroom, "north");

	Exit* kitchen_to_storage = new Exit("It seems to be a entrance to a storage room.", "", kitchen, storage_room, true, true, storage_key);
	Exit* storage_to_kitchen = new Exit("To the kitchen.", "", storage_room, kitchen, false, false, NULL);

	kitchen->AddExit(kitchen_to_storage, "east");
	storage_room->AddExit(storage_to_kitchen, "west");

	//END EXITS

	//GAME (add rooms)
	rooms.push_back(living_room);

	//PLAYER
	player = new Player("Player", "The person who is trapped inside the house.", living_room);

	//TEST
}

World::~World() {

}

bool World::Interaction(const string& input) {

	if (!hasWin) {
		bool response = true;

		vector<string> tokens;
		if (!input.empty()) {
			istringstream iss(input);
			copy(istream_iterator<string>(iss),
				istream_iterator<string>(),
				back_inserter(tokens));
		}

		if (tokens[0] == "combine") {
			player->Combine(tokens, combinables, combine_to);
		}
		else if (tokens[0] == "open") {
			player->Open(tokens);
		}
		else if (tokens.size() == 1) {
			if (tokens[0] == "investigate" || tokens[0] == "look") {
				player->Investigate();
			}
			else if (tokens[0] == "hi" || tokens[0] == "hello") {
				cout << "There is nobody here, you are alone... \n";
			}
			else if (tokens[0] == "pockets") {
				player->ShowInventory();
			}
			else if (tokens[0] == "north" || tokens[0] == "east" || tokens[0] == "west" || tokens[0] == "south") {
				if (player->Move(tokens[0])) {
					player->Investigate();
					if (player->location->name == "Exit") {
						hasWin = true;
						cout << "\nYou can exit the game by typing \"quit\".\n";
						cout << "Thanks for playing!\n";
					}
				}
			}
			else {
				response = false;
			}
		}
		else if (tokens.size() == 2) {
			if (tokens[0] == "use" || tokens[0] == "read") {
				player->UseItem(tokens[1]);
			}
			else if (tokens[0] == "boil") {
				player->BoilItem(tokens[1], cookers_working, stkey_instance);
			}
			else if (tokens[0] == "investigate" || tokens[0] == "look") {
				player->InvestigateItem(tokens[1]);
			}
			else if (tokens[0] == "drop") {
				player->DropItem(tokens[1]);
			}
			else if (tokens[0] == "take") {
				player->PickUpItem(tokens[1]);
			}
			else {
				response = false;
			}
		}
		else if (tokens.size() == 3) {
			if (tokens[0] == "lift" && tokens[1] == "the" && tokens[2] == "mattress") {
				player->LiftTheMattress(wckey_dropped, wckey_instance);
			}
			else if (tokens[0] == "turn" && tokens[1] == "on" && tokens[2] == "cookers") {
				player->TurnOnCookers(cookers_working);
			}
			else if (tokens[0] == "move") {
				player->PlayVatPuzzle(tokens, water_puzzle_complete, winkey_instance, vat_game);
			}
			else {
				response = false;
			}
		}
		else {
			response = false;
		}
		return response;
	}
	else {
		cout << "You can exit the game by typing \"quit\".\n";
		cout << "Thanks for playing!\n";
		return true;
	}
}