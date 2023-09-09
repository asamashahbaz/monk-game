#pragma once
#include "Room.h"

class ArmoryRoom: public Room {
public:
	ArmoryRoom(Dungeon* dungeon);
	void printRoomArt() override;
};
