#pragma once
#include "Room.h"

class MonsterRoom: public Room {
public:
	MonsterRoom(Dungeon* dungeon);
	void printRoomArt() override;
};