#pragma once
#include "Room.h"

class TreasureRoom: public Room {
public:
	TreasureRoom(Dungeon* dungeon);
	void printRoomArt() override;
};