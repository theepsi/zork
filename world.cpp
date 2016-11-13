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

World::World() {
	//GAME Entities...


	//ROOMS

	Room* living_room = new Room("Living Room", "The living room of the house.");
	Room* bath_room = new Room("Bath Room", "This is the bath room.");
	Room* storage_room = new Room("Storage Room", "Here you can see a lot of things.");
	Room* kitchen = new Room("Kitchen", "An Old Kitchen with some dishes.");
	Room* big_room = new Room("Big Room", "A very clean room, with a big bed.");
	Room* win_room = new Room("Win!", "You win the game, you scaped the room!");

	//ITEMS
	Item* book = new Item("book", "Description of the game.", false);
	Item* letter = new Item("letter", "Welcome to the game letter.", true);
	Item* clock = new Item("clock", "The clock is broken, it marks 02:27 p.m.", false);
	Item* picture = new Item("picture", "A bad imitation of the Van Gogh picture \"Bedroom in Arles\", the bedding is green...", false);
	Vault* security_box = new Vault("security_box", "It is a small security box. Above the keyboard it says \"24 hours\".", "1427");
	Item* bookcase = new Item("bookcase", "There are a lot of books but there is one that stands out above the others.", false);
	Item* false_book = new Item("false_book", "This book is fake, it seems to have something inside.", false);
	Item* cardboard = new Item("cardboard", "A piece of cardboard that contains some random letters in random positions...", true);

	Item* blackboard = new Item("blackboard", "A blackboard on the wall that says: BXPW WOK ZDWWGKJJ", false);

	picture->AddEntity(security_box);

	living_room->AddEntity(book);
	living_room->AddEntity(letter);
	living_room->AddEntity(clock);
	living_room->AddEntity(picture);

	// Add rooms to the game.
	rooms.push_back(living_room);


	//TODO: Create Keys to open doors.
	Item* bedroom_key = new Item("bkey", "The key of the bedroom.", true);

	security_box->AddEntity(bedroom_key);

	//EXITS

	Exit* living_to_bathroom = new Exit("A wooden door.", "", living_room, bath_room, true, true, NULL);
	Exit* living_to_win = new Exit("A very heavy door.", "", living_room, win_room, true, true, NULL);
	Exit* living_to_bigroom = new Exit("A normal door.", "", living_room, big_room, true, true, bedroom_key);
	Exit* living_to_kitchen = new Exit("It seams like a kitchen.", "", living_room, kitchen, false, false, NULL);

	living_room->AddExit(living_to_bathroom, "west");
	living_room->AddExit(living_to_win, "north");
	living_room->AddExit(living_to_bigroom, "south");
	living_room->AddExit(living_to_kitchen, "east");

	Exit* bathroom_to_livingroom = new Exit("To Living room", "", bath_room, living_room, false, false, NULL);
	Exit* kitchen_to_livingroom = new Exit("To Living room", "", kitchen, living_room, false, false, NULL);
	Exit* bigroom_to_livingroom = new Exit("To Living room", "", big_room, living_room, false, false, NULL);

	bath_room->AddExit(bathroom_to_livingroom, "east");
	kitchen->AddExit(kitchen_to_livingroom, "west");
	big_room->AddExit(bigroom_to_livingroom, "north");

	Exit* kitchen_to_storage = new Exit("It seams to be a entrance to a storage", "", kitchen, storage_room, true, true, NULL);
	Exit* storage_to_kitchen = new Exit("To Kitchen room", "", storage_room, kitchen, true, false, NULL);

	kitchen->AddExit(kitchen_to_storage, "east");
	storage_room->AddExit(storage_to_kitchen, "west");
	

	//PLAYER
	player = new Creature("Player", "The person who is trapped inside the house.", living_room);

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

	if (tokens.size() == 1) {
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

		if (tokens[0] == "investigate") {
			if (tokens[1] != "") {
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
		if (tokens[0] == "open") {
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