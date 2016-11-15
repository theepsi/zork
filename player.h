#ifndef _player
#define _player

#include <vector>
#include "creature.h"
#include "world.h"

class Room;

class Player : public Creature {
public:
	Player(const string& name, const string& description, Room* location);
	~Player();
	void Investigate();
	void InvestigateItem(const string& item_name);
	bool Move(const string& direction);
	void OpenDoor(const string& direction, const string& key_name);
	void UseItem(const string& item_name);
	void ShowInventory();
	void PickUpItem(const string& item_name);
	void DropItem(const string& item_name);
	void DropItem(const string& item_name, const string& destination);
	void Open(vector<string> tokens);

	void Combine(vector<string> tokens, map<Item*, list<Item*>> combinables, map<string, list<Item*>> combine_to);
	void BoilItem(const string& item_name, bool cookers_working, Item* stkey_instance);
	void LiftTheMattress(bool &wckey_dropped, Item* wckey_instance);
	void TurnOnCookers(bool &cookers_working);
	void PlayVatPuzzle(vector<string> tokens, bool &water_puzzle_complete, Item* winkey_instance, map<string, Vat*> vat_game);
	void ShowVats(map<string, Vat*> vat_game);
};

#endif

