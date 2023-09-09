#pragma once

#include <iostream>
#include <sstream>

#include "Misc/Observer.h"

#include "Misc/Utils.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

class Game: public Observer {
	Utils::Difficulty difficulty;
	std::stringstream ss;
public:
	void initialize();
	explicit Game(Utils::Difficulty difficulty);

private:
	void difficultySettings();
	static void showTutorial();
	void setupGame();
	void startGame(const string& name, const string& desc);
	void update(const std::string& message, bool log = false, bool onlyLog = false) override;
	void addToLog(const string& message);
	void logToFile() const;
};