#include <iostream>
#include "player.h"
#include "room.h"
#include "item.h"
#include "exit.h"
#include "vat.h"
#include "vault.h"

Player::Player(const string& name, const string& description, Room* location) :
	Creature(name, description, location) {}

Player::~Player() {

}

void Player::Investigate() {
	location->Investigate();

}

void Player::InvestigateItem(const string& item_name) {
	if (item_name != "security_box") {
		Entity* ent = location->GetEntityByName(item_name);
		if (ent != NULL) {
			ent->Investigate();
			for (list<Entity*>::iterator it = ent->contains.begin(); it != ent->contains.cend(); ++it) {
				Entity* ent = *it;
				Entity* check = location->GetEntityByName(ent->name);
				if (check == NULL) {
					location->AddEntity(ent);
				}
			}
			ent->DeleteContains();
		}
		else {
			Entity* ent = GetEntityByName(item_name);
			if (ent != NULL) {
				ent->Investigate();
			}
			else {
				cout << "You can not investigate that.\n";
			}
		}
	}
	else {
		cout << "You can not investigate that.\n";
	}
}

bool Player::Move(const string& direction) {
	if (location->exits.find(direction) != location->exits.end()) {
		Exit* exit = location->exits[direction];
		if (exit->closed) {
			cout << "The door is closed.\n";
			return false;
		}
		location = exit->destination;

		return true;
	}
	else {
		cout << "There is no way in that direction.\n";
		return false;
	}
}

void Player::OpenDoor(const string& direction, const string& key_name) {
	if (location->exits.find(direction) != location->exits.end()) {
		Exit* exit = location->exits[direction];
		if (!exit->closed && !exit->locked) {
			cout << "The door is already open.\n";
		}
		else if (key_name != "") {
			Entity* key = GetEntityByName(key_name);
			if (key == NULL) {
				cout << "You do not have that key in your pockets.\n";
			}
			else {
				Exit* exit = location->exits[direction];
				if (exit->locked) {
					if (exit->key == (Item*)key) {
						cout << "You open the door.\n";
						exit->locked = false;
						exit->closed = false;
					}
					else {
						cout << "You can not open this door with this item.\n";
					}
				}
				else {
					cout << "This door is already open.\n";
				}
			}
		}
		else {
			if (((Exit*)location->exits[direction])->locked) {
				cout << "Door is locked by key.\n";
			}
			else {
				if (((Exit*)location->exits[direction])->closed) {
					cout << "The door is open now.\n";
					((Exit*)location->exits[direction])->closed = false;
				}
				else {
					cout << "The door is already open.\n";
				}
			}
		}
		
	}
	else {
		cout << "The is no door in that direction.\n";
	}
}

void Player::UseItem(const string& item_name) {
	Entity* ent = location->GetEntityByName(item_name);
	if (ent != NULL) {
		((Item*)ent)->Use();
	}
	else {
		Entity* ent = GetEntityByName(item_name);
		if (ent != NULL) {
			((Item*)ent)->Use();
		}
		else {
			cout << "This item does not exist in your pockets or in the room.\n";
		}
	}
}

void Player::ShowInventory() {

	if (!contains.empty()) {
		for (list<Entity*>::iterator it = contains.begin(); it != contains.cend(); ++it) {
			Entity* ent = *it;
			cout << "\t" << ent->name << ":\t";
			cout << ent->description << "\n";
		}
	}
	else {
		cout << "You have nothing in your pockets.\n";
	}
}

void Player::PickUpItem(const string& item_name) {
	if (contains.size() < 3) {
		Entity* item = location->GetEntityByName(item_name);
		if (item != NULL) {
			if (((Item*)item)->pickable) {
				location->contains.remove(item);
				contains.push_back(item);

				cout << "You have taken: " << item->name << ".\n";
			}
			else {
				cout << "You can not take that item.\n";
			}

		}
		else {
			cout << "There is no item like this here.\n";
		}
	}
	else {
		cout << "You do not have enough space in your pockets. Drop an item to be able to take something you want.\n";
	}	
}

void Player::DropItem(const string& item_name) {
	Entity* item = GetEntityByName(item_name);
	if (item != NULL) {
		contains.remove(item);
		location->contains.push_back(item);

		cout << "You have dropped: " << item->name << ".\n";
	}
	else {
		cout << "There is no item like that in your pockets.\n";
	}
}

void Player::DropItem(const string& item_name, const string& destination) {
	Entity* item = GetEntityByName(item_name);
	Entity* dest = location->GetEntityByName(destination);
	if (item != NULL) {
		if (dest != NULL) {
			if (((Item*)dest)->canContains) {
				contains.remove(item);
				dest->contains.push_back(item);

				cout << "You have dropped: " << item->name << " on " << dest->name << ".\n";
			}
			else {
				cout << "You can not drop that item on that destination.\n";
			}
		}
		else {
			cout << "You can not drop that item on that destination.\n";
		}
	}
	else {
		cout << "There is no item like that in your pockets.\n";
	}
}

void Player::Open(vector<string> tokens) {
	if (tokens.size() == 1) {
		cout << "To open what?\n";
	}
	else {
		if (tokens[1] == "security_box") {
			if (tokens.size() == 2) {
				Entity* ent = location->GetEntityByName(tokens[1]);
				if (ent != NULL) {
					Vault* vault = (Vault*)ent;
					if (!vault->closed) {
						vault->Investigate();
						for (list<Entity*>::iterator it = vault->contains.begin(); it != vault->contains.cend(); ++it) {
							Entity* ent = *it;
							Entity* check = location->GetEntityByName(ent->name);
							if (check == NULL) {
								location->AddEntity(ent);
							}
						}
						vault->DeleteContains();
					}
					else {
						cout << "You forgot to enter the PIN.\n";
					}
				}
				else {
					cout << "You can not see that thing.\n";
				}
			}
			else if (tokens.size() == 3) {
				Entity* ent = location->GetEntityByName(tokens[1]);
				if (ent != NULL) {
					Vault* vault = (Vault*)ent;
					if (vault->OpenVault(tokens[2])) {
						for (list<Entity*>::iterator it = ent->contains.begin(); it != ent->contains.cend(); ++it) {
							Entity* ent = *it;
							Entity* check = location->GetEntityByName(ent->name);
							if (check == NULL) {
								location->AddEntity(ent);
							}
						}
						vault->DeleteContains();
					}
				}
				else {
					cout << "You can not see that thing.\n";
				}
			}
			else {
				cout << "You can not use more than one PIN.\n";
			}
		}
		else if (tokens[1] == "door") {
			if (tokens.size() == 2) {
				cout << "Which door do you want to open?\n";
			}
			else {
				cout << "You can not do that.\n";
			}
		}
		else if (tokens[1] == "north" || tokens[1] == "east" || tokens[1] == "west" || tokens[1] == "south") {
			if (tokens.size() == 2) {
				cout << "What do you want to open at " << tokens[1] << "?\n";
			}
			else if (tokens.size() == 3) {
				if (tokens[2] == "door") {
					OpenDoor(tokens[1], "");
				}
				else {
					cout << "You can not do that.\n";
				}
			}
			else if (tokens.size() == 5) {
				if (tokens[2] == "door" && tokens[3] == "with") {
					OpenDoor(tokens[1], tokens[4]);
				}
				else {
					cout << "You can not do that.\n";
				}
			}
			else {
				cout << "You can not do that.\n";
			}
			
		}
		else {
			cout << "You can not open this...\n";
		}
	}
}

void Player::Combine(vector<string> tokens, map<Item*, list<Item*>> combinables, map<string, list<Item*>> combine_to) {
	bool items_on_pockets = true;

	list<string> items;
	for (int i = 1; i < tokens.size(); ++i) {
		items.push_back(tokens[i]);
	}

	if (items.size() >= 2) {
		for (list<string>::iterator it = items.begin(); it != items.cend() && items_on_pockets; ++it) {
			Entity* ent = GetEntityByName(*it);
			if (ent == NULL) {
				items_on_pockets = false;
			}
		}
		if (items_on_pockets) {
			bool can_combine = false;
			Item* result_item = NULL;

			if (combine_to.find(items.front()) != combine_to.end()) {
				list<Item*> list_items = combine_to[items.front()];
				for (list<Item*>::iterator it = list_items.begin(); it != list_items.cend() && !can_combine; ++it) {
					can_combine = true;
					Item* item = *it;
					if (combinables.find(item) != combinables.end()) {
						result_item = item;
						list<Item*> check_list = combinables[item];
						if (check_list.size() == items.size()) {
							for (list<string>::iterator it = items.begin(); it != items.cend() && can_combine; ++it) {
								Item* token_item = (Item*)GetEntityByName(*it);
								if (find(check_list.begin(), check_list.end(), token_item) == check_list.end()) {
									can_combine = false;
								}
							}
						}
					}
				}
				if (can_combine) {
					AddEntity(result_item);
					for (string item : items) {
						DeleteEntityByName(item);
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
	else if (items.size() == 1) {
		cout << "You can not combine just one item.\n";
	}
	else{
		cout << "Which items do you want to combine?\n";
	}
}

void Player::BoilItem(const string& item_name, bool cookers_working, Item* stkey_instance) {
	if (item_name == "ice_cube") {
		Entity* check = GetEntityByName(item_name);
		if (check != NULL) {
			if (cookers_working) {
				cout << "The ice is melted, a key has been revealed in the water.\n";
				location->AddEntity(stkey_instance);
				contains.remove(check);
			}
			else {
				cout << "Cookers are not working.\n";
			}
		}
		else {
			cout << "You dont have that item in your pockets.\n";
		}
	}
	else{
		cout << "You can not boil that item.\n";
	}
	
}

void Player::LiftTheMattress(bool &wckey_dropped, Item* wckey_instance) {
	if (location->name == "Bedroom" && !wckey_dropped) {
		location->AddEntity(wckey_instance);
		cout << "You lift the mattress and a key has fallen to the floor.\n";
		wckey_dropped = true;
	}
	else {
		cout << "You lift the mattress and nothing happens.\n";
	}
}

void Player::TurnOnCookers(bool &cookers_working) {
	if (location->name == "Kitchen") {
		if (!cookers_working) {
			if (GetEntityByName("lighter") != NULL) {
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
		cout << "To turn on what?\n";
	}
}

void Player::PlayVatPuzzle(vector<string> tokens, bool &water_puzzle_complete, Item* winkey_instance, map<string, Vat*> vat_game) {
	if (location->name == "Storage Room") {
		if (!water_puzzle_complete) {
			Vat* source;
			Vat* dest;
			if (tokens[1] != tokens[2]) {
				source = vat_game[tokens[1]];
				dest = vat_game[tokens[2]];

				if (source->filled != 0) {
					source->MoveWater(dest);
					ShowVats(vat_game);
					if (vat_game["a"]->filled == 8 && vat_game["b"]->filled == 8) {
						cout << "You have completed the puzzle. A key appears on the wall.\n";
						location->AddEntity(winkey_instance);
						water_puzzle_complete = true;
					}
				}
				else {
					cout << "Source vat is empty.\n";
				}

			}
			else {
				cout << "You can not move water from the same source to the same destination.\n";
			}
		}
		else {
			cout << "You already solved this puzzle.\n";
		}
	}
	else {
		cout << "You can not do that here.\n";
	}

	
}
void Player::ShowVats(map<string, Vat*> vat_game) {
	if (location->name == "Storage Room") {
		cout << "a: " << vat_game["a"]->filled << "L/16L\n";
		cout << "b: " << vat_game["b"]->filled << "L/9L\n";
		cout << "c: " << vat_game["c"]->filled << "L/7L\n";
	}
	else {
		cout << "You can not do that here.\n";
	}
}

