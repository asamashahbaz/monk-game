﻿#include "TreasureRoom.h"
#include <iostream>

#include "../Misc/Utils.h"

using namespace std;
using namespace Utils;

TreasureRoom::TreasureRoom(Dungeon* dungeon): Room("Treasure Room", Type::Treasure, dungeon) {}

void TreasureRoom::printRoomArt() {
	std::cout << styles.at("TRS") << R"(
  ___________                                                   __________                       
  \__    ___/______   ____ _____    ________ _________   ____   \______   \ ____   ____   _____  
    |    |  \_  __ \_/ __ \\__  \  /  ___/  |  \_  __ \_/ __ \   |       _//  _ \ /  _ \ /     \ 
    |    |   |  | \/\  ___/ / __ \_\___ \|  |  /|  | \/\  ___/   |    |   (  <_> |  <_> )  Y Y  \
    |____|   |__|    \___  >____  /____  >____/ |__|    \___  >  |____|_  /\____/ \____/|__|_|  /
                         \/     \/     \/                   \/          \/                    \/
	)" << R"(
                 ______________________________________________________________ 
                |'`--...___                                           __,,...--| 
                |          '.      .=""`;=.,                     .-'''         | 
                |      _,-''|  ,-"_,=""     `"=.,                |`-.._        | 
                |  ,,-'   | |  "=._o`"-._        `"=.            |     ``-.._  | 
                |''      () |      `"=._o`"=._      _`"=._       |           `-| 
                |  ,   ('   |           :=._o "=._."_.-="'"=.,   | .           | 
                | |, ('     |    __.--" , ; `"=._o." ,-"""-._ ". | |`.         | 
                | |    ,|   | ._"  ,. .` ` `` ,  `"-._"-._   ". '| | |         | 
                |    .' |   | |o`"=._` , "` `; .". ,  "-._"-._; ;| | |         | 
                |    |  |   | | ;`-.o`"=._; ." ` '`."\` . "-._ / | | |  |`-.   | 
                |    |  |   | |o;    `"-.o`"=._``  '` " ,__.--o; | o |  |/\|   | 
                |    |  |   | | ;     (#) `-.o `"=.`_.--"_o.-; ; | | |  |`.|   | 
                |    |  |   | |o;._    "      `".o|o_.--"    ;o; | | |  |\/|   | 
                |    |  |   |  "=._o--._        ; | ;        ; ; | | |   `.|   | 
                |    |o |   |       "=._o--._   ;o|o;     _._;o; | | |     '   | 
                |    |  |  /             "=._o._; | ;_.--"o.--"   \| |         | 
                |    |  | /                   "=.o|o_.--""         \ |         | 
                |    |  |/                                          \|         | 
                |____|__/____________________________________________\_________|
	)" << styles.at("RESET") << endl << endl;
}