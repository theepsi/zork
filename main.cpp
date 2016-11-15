#include <iostream>
#include <string>
#include "world.h"

using namespace std;


int main() {
	cout << "\n";
	cout << "->Welcome to my Zork version - Zork: Room Escape!\n";
	cout << "\n";
	cout << " _________________ _   __                                    \n";
	cout << "|___  /  _  | ___ \\ | / /                                    \n";
	cout << "   / /| | | | |_/ / |/ /                                     \n";
	cout << "  / / | | | |    /|    \\                                     \n";
	cout << "./ /__\\ \\_/ / |\\ \\| |\\  \\                                    \n";
	cout << "\\_____/\\___/\\_| \\_\\_| \\_/                                    \n";
	cout << "\n";
	cout << "\n";
	cout << "______ _____  ________  ___  _____ _____ _____   ___  ______ _____ \n";
	cout << "| ___ \\  _  ||  _  |  \\/  | |  ___/  ___/  __ \\ / _ \\ | ___ \\  ___|\n";
	cout << "| |_/ / | | || | | | .  . | | |__ \\ `--.| /  \\// /_\\ \\| |_/ / |__  \n";
	cout << "|    /| | | || | | | |\\/| | |  __| `--. \\ |    |  _  ||  __/|  __| \n";
	cout << "| |\\ \\\\ \\_/ /\\ \\_/ / |  | | | |___/\\__/ / \\__/\\| | | || |   | |___ \n";
	cout << "\\_| \\_|\\___/  \\___/\\_|  |_/ \\____/\\____/ \\____/\\_| |_/\\_|   \\____/ \n";
	cout << "\n";
	cout << "\n";
	cout << "You suddenly wake up in a strange room, you dont know why you are here.\nMaybe you need to start investigating.\n";
	
	string input;

	World escape_room;
	
	while (1) {
		cout << "\n";
		cout << ">";
		getline(cin, input);
		if (input != "") {
			if (input == "quit") {
				break;
			}
			if (input == "help" || input == "h") {
				cout << "HELP\n\n";

				cout << "History: \n";
				cout << "You suddenly wake up in a strange room, you dont know why you are here.\nMaybe you need to start investigating.\n";

				cout << "Basic commands: \n";

				cout << "\n1. Game \n";
				cout << "\t- quit -> exit the game.\n";

				cout << "\n2. Movement \n";
				cout << "\t- north | east | west | south -> to visit the other house's areas.\n";

				cout << "\n3. Interaction \n";
				cout << "\t- investigate | look -> player looks at the whole room and list every visible item.\n";
				cout << "\t- investigate | look [item_name] -> player investigates the item's content. The elements from the item's content will be accesible from the room after executing this command (they will become visible).\n";
				cout << "\t- use | read [item_name] -> will show the advanced description for that item if it has.\n";
				cout << "\t- pockets -> this command open player's inventory.\n";
				cout << "\t- take [item_name] -> player takes an item from the room.\n";
				cout << "\t- drop [item_name] -> player drops an item to the room.\n";
				cout << "\t- combine [list_of_items] -> player can combine some items from its inventory by passing them throught the list. A successful combination will delete those items and create the new combinated one.\n";
				cout << "\t- open [north | east | west | south] door -> player can open unlocked doors with this command.\n";
				cout << "\t- open [north | east | west | south] door with [item_name] -> player can open locked doors with this command if it has the key in its inventory.\n";
				cout << "\t- open [vault_name] -> player can open unlocked vaults.\n";
				cout << "\t- open [vault_name] [pin] -> player can open vaults with a PIN. The elements from vault's content will be accesible from the room after executing this command (they will become visible).\n";
			}
			else if (!escape_room.Interaction(input)) {
				cout << "No idea how to do that...\n";
			}
		}
		else {
			cout << "Please type something to execute an action (you can type help for more information).\n";
		}
	}

	return 0;
}
