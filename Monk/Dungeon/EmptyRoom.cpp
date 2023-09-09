﻿#include "EmptyRoom.h"
#include <iostream>

#include "../Misc/Utils.h"

using namespace std;
using namespace Utils;

EmptyRoom::EmptyRoom(Dungeon* dungeon): Room("Empty Room", Type::Empty, dungeon) {}

void EmptyRoom::printRoomArt() {
	std::cout << styles.at("EMT") << R"(
___________               __           __________                       
\_   _____/ _____ _______/  |_ ___.__. \______   \ ____   ____   _____  
 |    __)_ /     \\____ \   __<   |  |  |       _//  _ \ /  _ \ /     \ 
 |        \  Y Y  \  |_> >  |  \___  |  |    |   (  <_> |  <_> )  Y Y  \
/_______  /__|_|  /   __/|__|  / ____|  |____|_  /\____/ \____/|__|_|  /
        \/      \/|__|         \/              \/                    \/
	)" << R"(
     ______________________________________________________________ 
    |'`--...___                                           __,,...--| 
    |          '.                                    .-'''         | 
    |      _,-''|                                    |`-.._        | 
    |  ,,-'   | |                                    |     ``-.._  | 
    |''      () |                                    |           `-| 
    |  ,   ('   |                                    | .           | 
    | |, ('     |                                    | |`.         | 
    | |    ,|   |                                    | | |         | 
    |    .' |   |                                    | | |         | 
    |    |  |   |____________________________________| | |  |`-.   | 
    |    |  |   |_\__________________\_____________\_| o |  |/\|   | 
    |    |  |   |  |                  |             || | |  |`.|   | 
    |    |  |   |  |                  |             || | |  |\/|   | 
    |    |  |   |--'------------------'-------------'| | |   `.|   | 
    |    |o |   |                                    | | |     '   | 
    |    |  |  /                                      \| |         | 
    |    |  | /                                        \ |         | 
    |    |  |/                                          \|         | 
    |____|__/____________________________________________\_________|
	)" << styles.at("RESET") << endl << endl;
}