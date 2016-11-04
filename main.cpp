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
	cout << "./ /__\\ \\_/ / \\  \\| |\\  \\                                    \n";
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

	//TODO: call here to Investigate to see the room's entities

	while (1) {
		cout << "\n";
		cout << ">";
		getline(cin, input);
		if (input == "quit") {
			break;
		}
		else if (escape_room.Interaction(input) == false) {
			cout << "I dont know how to tho that...\n";
		}
	}

	cout << "\n Good bye! Thanks for playing! \n";

	return 0;
}
