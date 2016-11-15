#include <iostream>
#include "vault.h"

Vault::Vault(const string& name, const string& description, const string& code) :
	Item(name, description, "", false, true),
	code(code), closed(true) {}

Vault::~Vault() {

}

bool Vault::OpenVault(const string& c) {
	if (closed) {
		if (code == c) {
			cout << "Correct PIN!\n";
			Investigate();
			closed = false;
			return true;
		}
		else {
			cout << "Incorrect PIN!\n";
			return false;
		}
	}
	else {
		Investigate();
		return true;
	}	
}
