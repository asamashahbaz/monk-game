#include "Character.h"

#include "../Misc/Utils.h"

Character::Character(const string& name, const string& desc, const int healthPoints, const int attackPoints) {
	this->name = name;
	this->desc = desc;
	this->healthPoints = healthPoints;
	this->attackPoints = attackPoints;
	this->maxHP = healthPoints;
	this->maxAP = attackPoints;
}

string& Character::getName() {
	return this->name;
}

void Character::setName(string& name) {
	this->name = name;
}

string& Character::getDesc() {
	return this->desc;
}

void Character::setDesc(string& desc) {
	this->desc = desc;
}

int Character::getHealthPoints() const {
	return this->healthPoints;
}

void Character::setHealthPoints(const int hp) {
	if (this->maxHP < hp)
		this->maxHP = hp;
	if (hp < 0) {
		this->healthPoints = 0;
		return;
	}
	this->healthPoints = hp;
}

int Character::getMaxHealthPoints() const {
	return this->maxHP;
}

void Character::setMaxHealthPoints(const int hp) {
	this->maxHP = hp;
}

int Character::getAttackPoints() const {
	return this->attackPoints;
}

void Character::setAttackPoints(const int ap) {
	if (this->maxAP < ap)
		this->maxAP = ap;
	this->attackPoints = ap;
}

int Character::getMaxAttackPoints() const {
	return this->maxAP;
}

void Character::setMaxAttackPoints(const int ap) {
	this->maxAP = ap;
}

void Character::attack(Character& target) const {
	std::cout << std::endl << this->name << " decided to attack!" << std::endl;
	if (Utils::random(1,2) == 1) {
		const int hpToSub = target.hasArmor() ? this->getAttackPoints() - 1 : this->getAttackPoints();
		target.setHealthPoints(target.getHealthPoints() - hpToSub);
		if (target.getHealthPoints() <= 0)
			target.setDead(true);
		std::cout << this->name << " dealt " << hpToSub << " damage to " << target.getName() << std::endl;
		if (hpToSub < this->getAttackPoints())
			std::cout << target.getName() << "'s Strong Armor absorbed 1 AP of " << this->name << std::endl;
		return;
	}
	std::cout << this->name << "'s attack failed!" << std::endl;
}

void Character::defend() {
	std::cout << std::endl << this->name << " decided to defend!" << std::endl;
	if (Utils::random(1, 2) == 1) {
		if (this->healthPoints < this->maxHP) {
			this->setHealthPoints(this->getHealthPoints() + 1);
			std::cout << this->name << " recovered 1 health point!" << std::endl;
		}
		std::cout << this->name << "'s defense was successful!" << std::endl;
		return;
	}
	std::cout << this->name << "'s defense failed!" << std::endl;
}

bool Character::isDead() const {
	return this->dead;
}

void Character::setDead(const bool dead) {
	this->dead = dead;
}

bool Character::hasArmor() const {
	return this->armor;
}

void Character::setArmor(const bool armor) {
	this->armor = armor;
}