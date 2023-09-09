#include "Room.h"
#include "../Misc/Utils.h"
using namespace std;
using namespace Utils;

Room::Room(const char* name, const Type type, Dungeon* dungeon) {
	this->name = name;
	this->type = type;
	this->dungeon = dungeon;
}

string& Room::getName() {
	return (this->name);
}

Room::Type Room::getType() const {
	return this->type;
}

void Room::reloadRoom() {
	clr();
	this->printRoomArt();
}

Dungeon* Room::getDungeon() const {
	return this->dungeon;
}