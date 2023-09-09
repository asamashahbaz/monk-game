#include "Monk.h"

Monk::Monk(const string& name, const string& desc, int healthPoints, int attackPoints)
	: Character(name, desc, healthPoints, attackPoints) {}

Monk::Monk(const string& name, const string& desc)
	: Character(name, desc, 15, 3) {}

void Monk::pray() {
	std::cout << name << " has decided to pray!" << std::endl;
	std::cout << "Their health points have been fully restored!" << std::endl;
	this->setHealthPoints(this->maxHP);
}

Room* Monk::getRoom() const {
	return this->currentRoom;
}

void Monk::setRoom(Room* room) {
	this->currentRoom = room;
	this->roomsVisited++;
}

int Monk::getRoomsVisited() const {
	return this->roomsVisited;
}
