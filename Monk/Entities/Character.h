#pragma once

#include <string>
#include <iostream>
using std::string;

class Character {
protected:
	string name;
	string desc;
	int healthPoints;
	int attackPoints;
	int maxAP;
	int maxHP;
	bool dead = false;
	bool armor = false;
public:
	Character(const string& name, const string& desc, int healthPoints, int attackPoints);
	string& getName();
	void setName(string& name);
	string& getDesc();
	void setDesc(string& desc);
	int getHealthPoints() const;
	void setHealthPoints(int hp);
	int getMaxHealthPoints() const;
	void setMaxHealthPoints(int hp);
	int getAttackPoints() const;
	void setAttackPoints(int ap);
	int getMaxAttackPoints() const;
	void setMaxAttackPoints(int ap);
	void attack(Character& target) const;
	void defend();
	bool isDead() const;
	void setDead(bool dead);
	bool hasArmor() const;
	void setArmor(bool armor);
};