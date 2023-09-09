#pragma once
#include "Room.h"

class EmptyRoom: public Room {
public:
	EmptyRoom(Dungeon* dungeon);
	void printRoomArt() override;
};