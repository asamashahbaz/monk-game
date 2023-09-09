#pragma once

#include <functional>
#include <string>
#include <vector>
#include "../Misc/Observable.h"
#include "Room.h"

namespace Utils {
	enum class Difficulty;
}

class Character;
class Monk;
class Goblin;

class Dungeon: public Observable {
	int armoryUsed = 0;
	int monsterRooms = 2;
	int rooms;
	std::vector<Room*> roomsList;
	Utils::Difficulty difficulty;
public:
	Dungeon(Utils::Difficulty difficulty);
	void beginExploration(const std::string& name, const std::string& desc);
	std::vector<Room*>* getRooms();
	Room* getRoomByType(Room::Type type) const;
private:
	std::vector<Room*> generateRooms(const int& rooms, const int& monsterRooms);
	Goblin spawnMonster();
	bool canTakeUpgrade(const bool& upgradeTaken, const Monk& player, const bool& print);
	void printPlayerTurn(Character& player, Character& goblin);
	void printMonsterTurn(Character& player, Character& goblin);
	void handleCombat(Monk& player, Character& monster);
	void handleEmpty(Monk& player);
	void handleArmory(Monk& player);
	void handleTreasure(Monk& player);
	Room* getRandomRoom();
};

inline Room* Dungeon::getRoomByType(Room::Type type) const {
	for (Room* room : roomsList) {
		if (room->getType() == type) {
			return room;
		}
	}
	return nullptr;
}