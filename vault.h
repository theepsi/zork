#ifndef _vault
#define _vault

#include "entity.h"
#include "item.h"

class Vault : public Item {
public:
	Vault(const string& name, const string& description, const string& code);
	~Vault();
	bool OpenVault(const string& c);
	
	const string code;
	bool closed;
};

#endif

