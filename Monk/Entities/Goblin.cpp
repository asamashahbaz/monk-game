#include "Goblin.h"

Goblin::Goblin(const string& name, const string& desc, const int healthPoints, const int attackPoints)
	:Character(name, desc, healthPoints, attackPoints) {}
Goblin::Goblin()
	:Character("Goblin", "A mischievous, extremely malicious Goblin!", 10, 2) {}