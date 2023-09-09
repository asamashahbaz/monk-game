#include "Dungeon.h"

#include <algorithm>
#include <random>
#include <vector>

#include "ArmoryRoom.h"
#include "EmptyRoom.h"
#include "MonsterRoom.h"
#include "TreasureRoom.h"
#include "../Entities/Monk.h"
#include "../Entities/Goblin.h"
#include "../Misc/Utils.h"

using namespace Utils;
using namespace std;

Dungeon::Dungeon(const Difficulty difficulty) {
	this->difficulty = difficulty;
	// Monsters: Easy = 2; Medium = 4; Hard = 6;
	monsterRooms = (difficulty == Difficulty::Easy ? 2 : (difficulty == Difficulty::Medium ? 4 : 6));
	rooms = monsterRooms + 4;
	generateRooms(monsterRooms + 4, monsterRooms);
}

vector<Room*> Dungeon::generateRooms(const int& rooms, const int& monsterRooms) {
	vector<Room*> dRooms;
	dRooms.reserve(this->rooms);
	dRooms.push_back(new EmptyRoom(this));
	for (int i = 0; i < monsterRooms; i++) {
		dRooms.push_back(new MonsterRoom(this));
	}
	dRooms.push_back(new ArmoryRoom(this));
	// +3 because we will have 1 Empty Room, 1 Armory Room and 1 Treasure Room which are mandatory
	// Subtract n of monster rooms + the other required rooms and fill the rest with random rooms
	for (int i = 0; i < this->rooms - (monsterRooms + 3); i++) {
		dRooms.push_back(getRandomRoom());
	}
	// Shuffle the order in which the rooms will be presented to the player
	std::shuffle(dRooms.begin(), dRooms.end(), std::random_device());
	// Finally add Treasure Room as the last room
	dRooms.push_back(new TreasureRoom(this));
	this->roomsList = dRooms;
	return dRooms;
}

Room* Dungeon::getRandomRoom() {
	const int id = random(1, 2);
	if (id == 1) {
		return new EmptyRoom(this);
	}
	return new ArmoryRoom(this);
}

Goblin Dungeon::spawnMonster() {
	Goblin goblin;
	switch (difficulty) {
	case Difficulty::Easy: {
		goblin.setAttackPoints(2);
		break;
	}
	case Difficulty::Medium: {
		goblin.setAttackPoints(3);
		goblin.setHealthPoints(12);
		break;
	}
	case Difficulty::Hard: {
		goblin.setAttackPoints(5);
		goblin.setHealthPoints(15);
		break;
	}
	}
	log("Monster Spawned\n\tName: " + goblin.getName() + "\n\tDesc: " + goblin.getDesc());
	log("\tMonster Stats:\n\t\tHP: " + std::to_string(goblin.getHealthPoints()) + "\n\t\tAP: " + std::to_string(goblin.getAttackPoints()) + "\n");
	return goblin;
}

void Dungeon::beginExploration(const std::string& name, const std::string& desc) {
	Monk player(name, desc);
	for (Room* room : roomsList) {
		if (player.isDead()) {
			log("\nGame lost...");
			break;
		}
		player.setRoom(room);
		log(room->getName());
		switch (room->getType()) {
		case Room::Type::Monster: {
			Goblin goblin = spawnMonster();
			player.getRoom()->reloadRoom();
			notify("You have come across " + styles.at("GRN") + goblin.getDesc() + styles.at("RESET"));
			notify("Defeat them to proceed to the next room...\n\n");
			halt();
			handleCombat(player, goblin);
			break;
		}
		case Room::Type::Empty: {
			handleEmpty(player);
			break;
		}
		case Room::Type::Armory: {
			handleArmory(player);
			break;
		}
		case Room::Type::Treasure: {
			handleTreasure(player);
			halt();
			break;
		}
		}
		
	}
}

std::vector<Room*>* Dungeon::getRooms() {
	return &(this->roomsList);
}

void Dungeon::printPlayerTurn(Character& player, Character& goblin) {
	notify(styles.at("CYN") + player.getName() + styles.at("RESET") + ": " + std::to_string(player.getHealthPoints()) + "/" + std::to_string(player.getMaxHealthPoints()) + " HP | " + std::to_string(player.getAttackPoints()) + " AP                                 " +
		styles.at("RED") + goblin.getName() + styles.at("RESET") + ": " + std::to_string(goblin.getHealthPoints()) + "/" + std::to_string(goblin.getMaxHealthPoints()) + " HP | " + std::to_string(goblin.getAttackPoints()) + " AP");
	notify(styles.at("CYN") + player.getDesc() + styles.at("RESET") + "\n");
}

void Dungeon::printMonsterTurn(Character& player, Character& goblin) {
	notify(styles.at("RED") + goblin.getName() + styles.at("RESET") + ": " + std::to_string(goblin.getHealthPoints()) + "/" + std::to_string(goblin.getMaxHealthPoints()) + " HP | " + std::to_string(goblin.getAttackPoints()) + " AP                                 " +
		styles.at("CYN") + player.getName() + styles.at("RESET") + ": " + std::to_string(player.getHealthPoints()) + "/" + std::to_string(player.getMaxHealthPoints()) + " HP | " + std::to_string(player.getAttackPoints()) + " AP");
	notify(styles.at("RED") + goblin.getDesc() + styles.at("RESET") + "\n");
}

void Dungeon::handleCombat(Monk& player, Character& monster) {
	const Character* currentTurn = &player;
	do {
		player.getRoom()->reloadRoom();
		if (currentTurn == &player) {
			string choice;
			printPlayerTurn(player, monster);
			notify(styles.at("CYN") + "It's your turn. Choose strategically!" + styles.at("RESET") + "\n", true);
			notify("1. Attack		2. Defend\n");
			crsr("Attack or defend?");
			getline(cin, choice);
			if (choice == "1") {
				player.attack(monster);
				log("Attacking");
				log("\tMonster HP: " + std::to_string(monster.getHealthPoints()) + "\n");
			}
			else if (choice == "2") {
				player.defend();
				log("Defending");
				log("\tPlayer HP: " + std::to_string(player.getHealthPoints()) + "\n");
			}
			else {
				handleWrongInput(choice);
				player.getRoom()->reloadRoom();
				continue;
			}
			currentTurn = &monster;
			halt();
		}
		else {
			printMonsterTurn(player, monster);
			notify(styles.at("RED") + "It's " + monster.getName() + "'s turn!" + styles.at("RESET") + "\n", true);
			if (random(1, 2) == 1) {
				monster.attack(player);
				log("Attacking");
				log("\tPlayer HP: " + std::to_string(player.getHealthPoints()) + "\n");
			}
			else {
				monster.defend();
				log("Defending");
				log("\tMonster HP: " + std::to_string(monster.getHealthPoints()) + "\n");
			}
			currentTurn = &player;
			halt();
		}
	} while (!monster.isDead() && !player.isDead());

	player.getRoom()->reloadRoom();
	if (monster.isDead())
		notify(monster.getName() + " has been defeated!\n", true);

	if (player.isDead())
		notify(player.getName() + " has been defeated!\n", true);
	
	halt();
}

void Dungeon::handleEmpty(Monk& player) {
	string option;
	bool hasPrayed = false;
	do {
		player.getRoom()->reloadRoom();
		notify("This room seems very peaceful. You can pray to restore your health!\n");
		notify(styles.at("CYN") + player.getName() + styles.at("RESET") + ": " + std::to_string(player.getHealthPoints()) + "/" + std::to_string(player.getMaxHealthPoints()) + " HP\n");
		notify((hasPrayed ? styles.at("STRIKE") + styles.at("RED") + "1. Pray" + styles.at("RESET") : "1. Pray") + "          2. Next Room\n");
		crsr("Pray or move to the next room?"); getline(cin, option);
		if (option == "1") {
			log("\tPrayed");
			if (!hasPrayed) {
				hasPrayed = true;
				const int hRecovered = player.getMaxHealthPoints() - player.getHealthPoints();
				player.setHealthPoints(player.getMaxHealthPoints());
				notify("\n" + styles.at("GRN") + "+" + std::to_string(hRecovered) + styles.at("RESET") + " HP recovered!");
				halt();
				continue;
			}
			notify("\n" + styles.at("RED") + "You have already prayed. Move to the next room!" + styles.at("RESET") + "\n");
		}
		else if (option == "2") {
			log("\tNext Room");
			break;
		}
		else {
			handleWrongInput(option);
			continue;
		}
		halt();
	} while (option != "2");
}

bool Dungeon::canTakeUpgrade(const bool& upgradeTaken, const Monk& player, const bool& print) {
	bool valid = true;
	if (upgradeTaken) {
		valid = false;
		if (print) {
			notify("\n" + styles.at("RED") + "You have already taken this upgrade!" + styles.at("RESET"));
			halt();
		}
	}
	if (armoryUsed >= 2) {
		valid = false;
		if (print) {
			notify("\n" + styles.at("RED") + "You have already used the Armory twice!" + styles.at("RESET"));
			halt();
		}
	}
	return valid;
}

void Dungeon::handleArmory(Monk& player) {
	string option;
	const int upgradeItem = random(0, 1);
	const int armorChance = random(0, 1);
	bool upgradeTaken = false;
	do {
		player.getRoom()->reloadRoom();
		notify("You have found the Armory!\nSo many things you could upgrade! But remember, you can only use the Armory twice.\n");
		notify(styles.at("MAG") + "                                Armory Used: "
			+ styles.at("RESET") + std::to_string(armoryUsed) + "/2\n");

		// Normally 2 upgrade items are available to the player.
		if (upgradeItem == 0) {

			// But if their difficulty is set to medium or higher, there is a chance for them to get this extra item
			// rather than the default item for upgradeItem = 0
			if (difficulty >= Difficulty::Medium) {
				if (armorChance == 1) {
					notify(styles.at("YEL") + "Strong Armor" + styles.at("RESET") + " is available to you. It absorbs " + styles.at("GRN") + "1 AP" + styles.at("RESET") + " each time the monster strikes.\n");

					if (!canTakeUpgrade(upgradeTaken, player, false))
						notify(styles.at("STRIKE") + styles.at("RED") + "1. Wear" + styles.at("RESET") + "          2. Next Room\n");
					else
						notify("1. Wear          2. Next Room\n");

					crsr("Take Strong Armor or go to the next room?"); getline(cin, option);
					if (option == "1") {
						log("\tWore Strong Armor");
						if (!canTakeUpgrade(upgradeTaken, player, true))
							continue;
						armoryUsed++;
						player.setArmor(true);
						notify("\nYou are now wearing a Strong Armor!");
						upgradeTaken = true;
						halt();
						continue;
					}
					if (option == "2") {
						log("\tNext Room");
						break;
					}
					handleWrongInput(option);
					continue;
				}
			}

			// They will get the default item for upgradeItem = 0 because armorChance was 0
			notify(styles.at("RED") + "Lethal Axe" + styles.at("RESET") + " is available to you. It inflicts " + styles.at("GRN") + "+2 extra damage" + styles.at("RESET") + " to the monster.\n");

			if (!canTakeUpgrade(upgradeTaken, player, false))
				notify(styles.at("STRIKE") + styles.at("RED") + "1. Equip" + styles.at("RESET") + "          2. Next Room\n");
			else
				notify("1. Equip          2. Next Room\n");

			crsr("Equip Lethal Axe or go to the next room?"); getline(cin, option);
			if (option == "1") {
				log("\tEquipped Lethal Axe");
				if (!canTakeUpgrade(upgradeTaken, player, true))
					continue;
				armoryUsed++;
				player.setAttackPoints(player.getAttackPoints() + 2);
				notify("\n" + styles.at("GRN") + "+2" + styles.at("RESET") + " AP. You are now more lethal than ever!");
				upgradeTaken = true;
				halt();
				continue;
			}
			if (option == "2") {
				log("\tNext Room");
				break;
			}
			handleWrongInput(option);
		}
		else {
			notify(styles.at("BLU") + "Witcher's Potion" + styles.at("RESET") + " is available to you. It adds " + styles.at("GRN") + "+5 to your max HP" + styles.at("RESET") + " and heals you by 5 HP!\n");

			if (!canTakeUpgrade(upgradeTaken, player, false))
				notify(styles.at("STRIKE") + styles.at("RED") + "1. Drink Potion" + styles.at("RESET") + "          2. Next Room\n");
			else
				notify("1. Drink Potion          2. Next Room\n");

			crsr("Take potion or go to the next room?"); getline(cin, option);
			if (option == "1") {
				log("\tDrank Witcher's Potion");
				if (!canTakeUpgrade(upgradeTaken, player, true))
					continue;
				armoryUsed++;
				player.setMaxHealthPoints(player.getMaxHealthPoints() + 5);
				player.setHealthPoints(player.getHealthPoints() + 5);
				notify("\n" + styles.at("GRN") + "+5" + styles.at("RESET") + " HP. You feel the energy rushing through your veins!");
				upgradeTaken = true;
				halt();
				continue;
			}
			if (option == "2") {
				log("\tNext Room");
				break;
			}
			handleWrongInput(option);
		}
	} while (option != "2");
}

void Dungeon::handleTreasure(Monk& player) {
	player.getRoom()->reloadRoom();
	log("\nGame Won!\nFinal Stats:");
	cout << styles.at("GLD") << R"(
                                   / \-------------------, 
                                   \_,|                  | 
                                      |     YOU WON!     | 
                                      |  ,----------------.
                                      \_/________________/ )" << endl << endl;
	notify(styles.at("GLD") + "                                        Monk's name: " + styles.at("RESET") + player.getName(), true);
	notify(styles.at("GLD") + "                                        Monk's description: " + styles.at("RESET") + player.getDesc(), true);
	notify(styles.at("GLD") + "                                        Monk's HP: " + styles.at("RESET") + std::to_string(player.getHealthPoints()) + "/" + std::to_string(player.getMaxHealthPoints()), true);
	notify(styles.at("GLD") + "                                        Rooms visited: " + styles.at("RESET") + std::to_string(player.getRoomsVisited()), true);
	notify(styles.at("GLD") + "                                        Monsters fought: " + styles.at("RESET") + std::to_string(monsterRooms), true);
	notify(styles.at("GLD") + "                                        Difficulty: " + styles.at("RESET") + coloredDifficulty(difficulty) + "\n", true);
}