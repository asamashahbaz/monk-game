#pragma once
#include "Character.h"

class Room;

class Monk: public Character {
	Room* currentRoom = nullptr;
	int roomsVisited = 0;
public:
	Monk(const string& name, const string& desc, int healthPoints, int attackPoints);
	Monk(const string& name, const string& desc);
	void pray();
	Room* getRoom() const;
	void setRoom(Room* room);
	int getRoomsVisited() const;
};