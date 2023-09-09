#pragma once
#include <string>

class Dungeon;

class Room {
protected:
	std::string name;
	Dungeon* dungeon;
public:
	enum class Type {
		Monster, Empty, Armory, Treasure
	};
	Room(const char* name, Type type, Dungeon* dungeon);
	virtual ~Room() = default;
	Type getType() const;
	virtual std::string& getName();
	virtual void printRoomArt() = 0;
	void reloadRoom();
	Dungeon* getDungeon() const;
private:
	Type type;
};