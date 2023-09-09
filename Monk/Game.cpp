#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Dungeon/Dungeon.h"

using namespace Utils;

Game::Game(const Difficulty difficulty) {
	Game::difficulty = difficulty;
}

void Game::initialize() {
	bool exit = false;
	do {
		string option;
		printTitle();
		setupMainMenu();
		cout << endl; crsr();
		getline(cin, option);
		cout << styles.at("RESET");
		if (option == "1")
			setupGame();
		else if (option == "2") {
			difficultySettings();
		} else if (option == "3") {
			showTutorial();
			halt();
		} else if (option == "4") {
			exit = true;
		} else
			handleWrongInput(option);
	} while (!exit);
	system("exit");
}

void Game::showTutorial() {
	clr();
	printTitle();
	cout << R"(
                                     How to play?                                    
                                                                                     
          You play as a Monk who is on the lookout for a long-lost treasure.         
         You will explore dungeons and fight monsters to get to the treasure.        
                                                                                     
            There are four types of rooms in a dungeon. They are randomly            
                               spawned for every game.                               
                     Below you will find details about each room.                    
                                                                                     
                                      EMPTY ROOM                                     
         In this room, you can pray to restore your character's health points        
                                       to full.                                      
                                                                                     
                                     MONSTER ROOM                                    
          This room hosts a monster that you will have to defeat to proceed          
       to the other rooms. The combat is set up to be turn-based and ends when       
         either the monster or the player have lost all their health points.         
         Both player and monster are able to attack or defend for each turn.         
           The outcome of their action is based on a 50% chance of success.          
         A successful attack will reduce the opponent's health points by the         
                      amount of attack points the attacker has.                      
       A successful defense will heal the entity performing the action by 1 hp.      
                                                                                     
                                     ARMORY ROOM                                     
       In this room, player can get 1 random item that will increase their odds      
                                 against the monster.                                
                      There are 3 items available in the Armory:                     
                   Lethal Axe: increase player's attack points by 2                  
             Witcher's Potion: increase your max health points limits by             
                         5 points and heals you by 5 points.                         
                 Strong Armor: absorbs 1 attack point of the monster.                
                                                                                     
                                    TREASURE ROOM                                    
           This is the last of the rooms, and the player wins upon finally           
                                getting to this room.                                
                                                                                     

	)";
}

void Game::difficultySettings() {
	do {
		clr();
		printTitle();
		string option;
		cout << "Current Difficulty: " << coloredDifficulty(difficulty) << endl << endl;
		cout << "What the different difficulty levels mean?" << endl;

		cout << endl << styles.at("CYN") << "Easy:" << styles.at("RESET");
		cout << R"(
    You will have to fight against 2 monsters.
    Monster's AP: 2
    Monster's HP: 10
    Items available in the Armory:
        + Lethal Axe
        + Witcher's Potion
        - Strong Armor)";

		cout << endl << endl << styles.at("YEL") << "Not So Easy:" << styles.at("RESET");
		cout << R"(
    You will have to fight against 4 monsters.
    Monster's AP: 3
    Monster's HP: 12
    Items available in the Armory:
        + Lethal Axe
        + Witcher's Potion
        + Strong Armor)";

		cout << endl << endl << styles.at("RED") << "Impossible:" << styles.at("RESET");
		cout << R"(
    You will have to fight against 6 monsters.
    Monster's AP: 5
    Monster's HP: 15
    Items available in the Armory:
        + Lethal Axe
        + Witcher's Potion
        + Strong Armor)" << endl << endl;
		cout << "1. Easy          2. Not So Easy          3. Impossible" << endl << endl;
		crsr("Set difficulty level:"); std::getline(cin, option);
		if (option == "1") {
			difficulty = Difficulty::Easy;
			cout << endl << "Difficulty set to " << coloredDifficulty(difficulty);
			mainMenu();
			break;
		}
		if (option == "2") {
			difficulty = Difficulty::Medium;
			cout << endl << "Difficulty set to " << coloredDifficulty(difficulty);
			mainMenu();
			break;
		}
		if (option == "3") {
			difficulty = Difficulty::Hard;
			cout << endl << "Difficulty set to " << coloredDifficulty(difficulty);
			mainMenu();
			break;
		}
		handleWrongInput(option);
	} while (true);
}

void Game::setupGame() {
	string name;
	string desc;
	do {
		clr();
		printTitle();
		crsr("Give your character a name");
		getline(cin, name);
		if (name.empty()) {
			cout << endl <<  styles.at("RED") << "Must provide a name!" << styles.at("RESET");
			halt();
			continue;
		}
		cout << endl; crsr("Briefly describe your character");
		getline(cin, desc);
		if (desc.empty()) {
			cout << endl << styles.at("RED") << "Must provide a description!" << styles.at("RESET");
			halt();
			continue;
		}
		startGame(name, desc);
	} while (name.empty() || desc.empty());
}

void Game::startGame(const string& name, const string& desc) {
	addToLog("Character created!\nName: " + name + "\nDesc: " + desc + "\n");
	auto dungeon = Dungeon(difficulty);
	dungeon.attach(this);
	dungeon.beginExploration(name, desc);
	logToFile();
}

void Game::update(const std::string& message, const bool log, const bool onlyLog) {
	if (!onlyLog)
		cout << message << endl;
	if (log) {
		if (!onlyLog) {
			string toSanitize = message;
			sanitizeString(toSanitize);
			addToLog(toSanitize);
			return;
		}
		addToLog(message);
	}
}

void Game::addToLog(const string& message) {
	ss << message << endl;
}

void Game::logToFile() const {
	std::ofstream logsFile("logs-" + std::to_string(time(nullptr)) + ".txt");
	logsFile << ss.str();
	logsFile.close();
}
