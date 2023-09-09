#pragma once
#include <string>
#include <map>

namespace Utils {
	enum class Difficulty {
		Easy, Medium, Hard
	};
	const std::map<std::string, std::string> styles = {
		{"RED", "\x1B[31m" },
		{"GRN", "\x1B[32m" },
		{"YEL", "\x1B[33m" },
		{"BLU", "\x1B[34m" },
		{"MAG", "\x1B[35m" },
		{"CYN", "\x1B[36m" },
		{"WHT", "\x1B[37m" },
		{"GLD", "\x1B[38;2;255;215;0m" },

		// Per room
		{"ARM", "\x1B[38;2;204;229;255m" },
		{"EMT", "\x1B[38;2;255;153;51m" },
		{"TRS", "\x1B[38;2;255;215;0m" },
		{"BOLD", "\x1B[1m" },
		{"ITALIC", "\x1B[3m" },
		{"STRIKE", "\x1B[9m" },
		{"RESET", "\x1B[0m" }
	};
	void crsr(const std::string& title = "");
	int random(int min, int max);
	void halt();
	void clr();
	void mainMenu();
	void handleWrongInput(const std::string& input);
	void printTitle();
	void setupMainMenu();
	std::string coloredDifficulty(Difficulty difficulty);
	void sanitizeString(std::string& input);
	void findAndReplaceAll(std::string& data, const std::string& match, const std::string& replace);
};
