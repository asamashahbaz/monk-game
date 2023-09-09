#include "Utils.h"

#include <iostream>
#include <random>
#include <regex>

namespace Utils {

	void crsr(const std::string& title) {
		std::cout << styles.at("CYN") + title + (title.empty() ? "" : " ") + "> " + styles.at("RESET");
	}
	int random(const int min, const int max) {
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> dist(min, max);
		return dist(engine);
	}
	void halt() {
		std::cout << styles.at("YEL") << std::endl;
		system("pause");
		std::cout << styles.at("RESET");
	}
	void clr() {
		system("cls");
	}
	void mainMenu() {
		std::cout << std::endl << std::endl << styles.at("YEL") << "Press ENTER to return to the main menu > " << styles.at("RESET");
		std::cin.ignore(100000, '\n');
	}
	void handleWrongInput(const std::string& input) {
		std::cout << std::endl << styles.at("RED") << "\"" << input << "\" is not a valid input!" << styles.at("RESET") << std::endl;
		halt();
		clr();
	}
	void printTitle() {
		clr();
		std::cout << styles.at("YEL") << R"(
       _ .-') _                  .-') _             ('-.                    .-') _  
      ( (  OO) )                ( OO ) )          _(  OO)                  ( OO ) ) 
       \     .'_ ,--. ,--.  ,--./ ,--,' ,----.   (,------. .-'),-----. ,--./ ,--,'  
       ,`'--..._)|  | |  |  |   \ |  |\'  .-./-') |  .---'( OO'  .-.  '|   \ |  |\  
       |  |  \  '|  | | .-')|    \|  | )  |_( O- )|  |    /   |  | |  ||    \|  | ) 
       |  |   ' ||  |_|( OO )  .     |/|  | .--, (|  '--. \_) |  |\|  ||  .     |/  
       |  |   / :|  | | `-' /  |\    |(|  | '. (_/|  .--'   \ |  | |  ||  |\    |   
       |  '--'  ('  '-'(_.-'|  | \   | |  '--'  | |  `---.   `'  '-'  '|  | \   |   
       `-------'  `-----'   `--'  `--'  `------'  `------'     `-----' `--'  `--'   
    )" << styles.at("RESET") << styles.at("CYN") << R"(                                                       A Monk's Treasure Hunt)"
			<< styles.at("RESET") << std::endl << std::endl << std::endl;
	}
	void setupMainMenu() {
		std::cout << R"(                                          MAIN MENU)" << std::endl;
		std::cout << styles.at("CYN") << R"(
  .----------.         .---------------.          .----------------.          .---------.                                                    
  | 1. Start |         | 2. Difficulty |          | 3. How to Play |          | 4. Exit |                                                     
  '----------'         '---------------'          '----------------'          '---------')" << styles.at("RESET") << std::endl;
	}
	std::string coloredDifficulty(const Difficulty difficulty) {
		return (difficulty == Difficulty::Easy ? styles.at("CYN") + "Easy" : (difficulty == Difficulty::Medium ? styles.at("YEL") + "Not So Easy" : styles.at("RED") + "Impossible")) + styles.at("RESET");
	}
	void sanitizeString(std::string& input) {
		for (const auto& p : styles)
		{
			findAndReplaceAll(input, p.second, "");
		}
	}

	void findAndReplaceAll(std::string& data, const std::string& match, const std::string& replace) {
		size_t pos = data.find(match);
		
		while (pos != std::string::npos)
		{
			data.replace(pos, match.size(), replace);
			
			pos = data.find(match, pos + replace.size());
		}
	}
}