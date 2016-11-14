#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "entity.h"
#include "creature.h"
#include "world.h"
#include "item.h"
#include "exit.h"
#include "vault.h"
#include "vat.h"

World::World() {
	//GAME Entities...
	
	//ROOMS

	Room* living_room = new Room("Living Room", "The living room of the house.");
	Room* big_room = new Room("Big Room", "A very clean room, with a big bed.");
	Room* bathroom = new Room("Bathroom", "This is the bath room.");
	Room* kitchen = new Room("Kitchen", "An old kitchen with some dishes.");
	Room* storage_room = new Room("Storage Room", "Here you can see a lot of things.");
	Room* win_room = new Room("Win!", "You win the game, you scaped the room!");

	//END ROOMS

	//KEYS
	//TODO: Create Keys to open doors.
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
	Item* cushion_red = new Item("cushion_red", "A red cushion.", "TODO", false);
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
	Item* cookers = new Item("cookers", "You can burn or melt things with this, but you need a flame first.", "You need a lighter to start cooking.", true);
	Item* fridge = new Item("fridge", "An old fridge.", "", false);
	Item* freezer = new Item("freezer", "A freezer inside the fridge.", "", false);
	Item* ice_cube = new Item("ice_cube", "A very solid and strong ice cube with something inside.", "", true);

	freezer->AddEntity(ice_cube);
	fridge->AddEntity(freezer);

	kitchen->AddEntity(cookers);
	kitchen->AddEntity(fridge);

	//Storage room items
	Item* letter_game = new Item("instructions", "Instructions for the water puzzle.", "You must fill with 8 liters of water both 16 and 9 liter vats, once you accomplish that, the key to the victory will be revealed to you.", false);
	Vat* water_vat_16 = new Vat("A-vat: 16L", "A vat with 16 liters of capacity.", 16, 16);
	Vat* water_vat_9 = new Vat("B-vat: 9L", "A vat with 9 liters of capacity.", 9, 0);
	Vat* water_vat_7 = new Vat("C-vat: 7L", "A vat with 7 liters of capacity.", 7, 0);

	vat_game["A"] = water_vat_16;
	vat_game["B"] = water_vat_9;
	vat_game["C"] = water_vat_7;

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
	player = new Creature("Player", "The person who is trapped inside the house.", living_room);

	//TEST
	/*player->AddEntity(perforated_envelope);
	player->AddEntity(cardboard);*/
	/*player->AddEntity(result_lighter);*/
	//player->AddEntity(stkey_instance);

}

bool World::Interaction(const string& input) {

	bool response = true;
	
	vector<string> tokens;
	if (!input.empty()) {
		istringstream iss(input);
		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(tokens));
	}

	if (tokens[0] == "combine") {
		bool items_on_pockets = false;
		if (tokens.size() > 2) {
			// Inventory checks
			for (string token : tokens) {
				if (token != "combine") {
					Entity* ent = player->GetEntityByName(token);
					if (ent != NULL) {
						items_on_pockets = true;
					}
					else {
						items_on_pockets = false;
						break;
					}
				}
			}
			if (items_on_pockets) {
				bool can_combine = false;
				Item* result_item = NULL;
				if (combine_to.find(tokens[1]) != combine_to.end()) {
					for (Item* item : combine_to[tokens[1]]) {
						if (combinables.find(item) != combinables.end()) {
							result_item = item;
							list<Item*> check_list = combinables[item];
							if (check_list.size() == tokens.size() - 1) {
								for (string token : tokens) {
									if (token != "combine") {
										Item* token_item = (Item*)player->GetEntityByName(token);
										if (find(check_list.begin(), check_list.end(), token_item) != check_list.end()) {
											can_combine = true;
										}
										else {
											can_combine = false;
											break;
										}
									}
								}
								if (can_combine) {
									break;
								}
							}
						}
					}
					if (can_combine) {
						player->AddEntity(result_item);
						for (string token : tokens) {
							if (token != "combine") {
								player->DeleteEntityByName(token);
							}
						}
						cout << "Item was successfully combined: " << result_item->name << "\n";
					}
					else {
						cout << "This objects are not combinables.\n";
					}
				}
				else {
					cout << "This objects are not combinables.\n";
				}
			}
			else {
				cout << "You do not have those items on your pockets.\n";
			}
		}
	}
	else if (tokens.size() == 1) {
		if (tokens[0] == "investigate") {
			player->Investigate();
		}
		else if (tokens[0] == "hi") {
			cout << "There is nobody here, you are alone... \n";
		}
		else if (tokens[0] == "pockets") {
			player->ShowInventory();
		}
		else if (tokens[0] == "north" || tokens[0] == "east" || tokens[0] == "west" || tokens[0] == "south") {
			if (player->Move(tokens[0])) {
				player->Investigate();
			}
		}
		else if (tokens[0] == "open") {
			cout << "What should I open?\n";
		}
		else {
			response = false;
		}
	}
	else if (tokens.size() == 2) {
		if (tokens[0] == "use" && tokens[1] == "cookers") {
			if (player->location->name == "Kitchen") {
				if (!cookers_working) {
					if (player->GetEntityByName("lighter") != NULL) {
						cout << "The cookers are working now. You can boil an item.\n";
						cookers_working = true;
					}
					else {
						cout << "You can not start fire from nothing. Be sure you have something that starts a flame.\n";
					}
				}
				else {
					cout << "Cookers are already working. You can boil an item.\n";
				}
			}
			else {
				response = false;
			}
		}
		else if (tokens[0] == "boil" && tokens[1] == "ice_cube") {
			Entity* check = player->GetEntityByName("ice_cube");
			if (check != NULL) {
				if (cookers_working) {
					cout << "The ice is melted, a key has been revealed in the water.\n";
					player->location->AddEntity(stkey_instance);
				}
				else {
					cout << "Cookers are not working.\n";
				}
			}
			else {
				cout << "You dont have that item in your pockets.\n";
			}
			
		}
		else if (tokens[0] == "read" | tokens[0] == "use") {
			if (tokens[1] != "") {
				Entity* ent = player->location->GetEntityByName(tokens[1]);
				if (ent != NULL) {
					((Item*)ent)->UseItem();
				}
				else {
					Entity* ent = player->GetEntityByName(tokens[1]);
					if (ent != NULL) {
						((Item*)ent)->UseItem();
					}
				}
			}
		}
		else if (tokens[0] == "investigate") {
			if (tokens[1] != "" && tokens[1] != "security_box") {
				Entity* ent = player->location->GetEntityByName(tokens[1]);
				if (ent != NULL) {
					ent->Investigate();
					for (list<Entity*>::iterator it = ent->contains.begin(); it != ent->contains.cend(); ++it) {
						Entity* ent = *it;
						Entity* check = player->location->GetEntityByName(ent->name);
						if (check == NULL) {
							player->location->AddEntity(ent);
						}						
					}
					ent->DeleteContains();
				}
				else {
					cout << "You can not investigate that.\n";
				}
			}
		}
		else if (tokens[0] == "open") {
			if (tokens[1] == "door") {
				cout << "Which door should I open?\n";
			}
			else if (tokens[1] == "security_box") {
				Entity* ent = player->location->GetEntityByName(tokens[1]);
				if (ent != NULL)
					if (((Vault*)ent)->closed) {
						cout << "You forget to say the secret PIN.\n";
					}
					else {
						ent->Investigate();
					}
				else
					cout << "I can not see that thing.\n";
			}
		}
		else if (tokens[0] == "drop") {
			if (tokens[1] != "") {
				player->DropItem(tokens[1]);
			}
		}
		else {
			response = false;
		}
	}
	else if (tokens.size() == 3) {
		if (tokens[0] == "pick") {
			if (tokens[1] == "up") {
				if (tokens[2] != "") {
					player->PickUpItem(tokens[2]);
				}
			}
		}
		else if (tokens[0] == "move" && !water_puzzle_complete) {
			Vat* source;
			Vat* dest;
			if (tokens[1] != tokens[2]) {
				
				source = vat_game[tokens[1]];
				dest = vat_game[tokens[2]];

				source->MoveWater(dest);
				cout << "A: " << vat_game["A"]->filled << "L/16L\n";
				cout << "B: " << vat_game["B"]->filled << "L/9L\n";
				cout << "C: " << vat_game["C"]->filled << "L/7L\n";

				if (vat_game["A"]->filled == 8 && vat_game["B"]->filled == 8) {
					cout << "You completed the puzzle. A key appears on the wall.\n";
					player->location->AddEntity(winkey_instance);
					water_puzzle_complete = true;
				}
			}
			
		}
		else if (tokens[0] == "lift" && tokens[1] == "the" && tokens[2] == "mattress") {
			if (player->location->name == "Big Room" && !wckey_dropped) {
				player->location->AddEntity(wckey_instance);
				cout << "You lift the mattress and a key has fallen to the floor.\n";
				wckey_dropped = true;
			}
		}
		else if (tokens[0] == "open") {
			if (tokens[1] == "north" || tokens[1] == "east" || tokens[1] == "west" || tokens[1] == "south") {
				if (tokens[2] == "door") {
					if ( ((Exit*)player->location->exits[tokens[1]])->locked) {
						cout << "Door is locked by key\n";
					}
					else {
						cout << "The door is already open.\n";
					}
				}
			}
			else if (tokens[1] == "security_box") {

				Entity* ent = player->location->GetEntityByName(tokens[1]);
				if (ent != NULL) {
					Vault* vault = (Vault*)ent;
					if (vault->OpenVault(tokens[2])) {
						for (list<Entity*>::iterator it = ent->contains.begin(); it != ent->contains.cend(); ++it) {
							Entity* ent = *it;
							Entity* check = player->location->GetEntityByName(ent->name);
							if (check == NULL) {
								player->location->AddEntity(ent);
							}						
						}
						vault->DeleteContains();
					}
				}
				else
					cout << "I can not see that thing.\n";
				
			}
		}
	}
	else if (tokens.size() == 5) {
		if (tokens[0] == "open") {
			if (tokens[1] == "north" || tokens[1] == "east" || tokens[1] == "west" || tokens[1] == "south") {
				if (tokens[2] == "door") {
					if (tokens[3] == "with") {
						if (tokens[4] != "") {
							if (player->OpenDoor(tokens[1], tokens[4])) {
								cout << "You open the door.\n";
							}
						}
					}
				}
			}
		}
	}
	return response;
}

World::~World() {

}