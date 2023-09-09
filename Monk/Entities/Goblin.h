#pragma once
#include "Character.h"

class Goblin: public Character {
public:
	Goblin(const string& name, const string& desc, int healthPoints, int attackPoints);
	Goblin();
};