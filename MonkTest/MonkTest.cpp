#include "pch.h"
#include "CppUnitTest.h"
#include "Dungeon/Dungeon.h"
#include "Dungeon/Room.h"
#include "Entities/Monk.h"
#include "Entities/Goblin.h"
#include "Misc/Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MonkTest
{
	TEST_CLASS(MonkTest)
	{
	public:
		TEST_METHOD(DungeonRoomsBasedOnDifficultyLevel) {
			constexpr size_t expectedNumberOfRooms =8;

			auto dungeon = Dungeon(Utils::Difficulty::Medium);
			
			Assert::IsNotNull(dungeon.getRooms());

			Assert::AreEqual(expectedNumberOfRooms, dungeon.getRooms()->size());
			
		}

		TEST_METHOD(DungeonHasThreeRequiredRooms) {
			const auto dungeon = Dungeon(Utils::Difficulty::Easy);
			
			Assert::IsNotNull(dungeon.getRoomByType(Room::Type::Monster));
			
			Assert::IsNotNull(dungeon.getRoomByType(Room::Type::Empty));
			
			Assert::IsNotNull(dungeon.getRoomByType(Room::Type::Treasure));
		}

		TEST_METHOD(PlayerMovesBetweenRooms) {
			Monk player("Monk", "A monk");
			auto dungeon = Dungeon(Utils::Difficulty::Easy);
			for (Room* room : *(dungeon.getRooms())) {
				player.setRoom(room);
				switch (room->getType()) {
				case Room::Type::Monster: {
					Assert::IsTrue(player.getRoom()->getType() == Room::Type::Monster);
					break;
				}
				case Room::Type::Empty: {
					Assert::IsTrue(player.getRoom()->getType() == Room::Type::Empty);
					break;
				}
				case Room::Type::Armory: {
					Assert::IsTrue(player.getRoom()->getType() == Room::Type::Armory);
					break;
				}
				case Room::Type::Treasure: {
					Assert::IsTrue(player.getRoom()->getType() == Room::Type::Treasure);
					break;
				}
				}
			}

			const size_t roomsVisitedByPlayer = player.getRoomsVisited();
			Assert::IsTrue(roomsVisitedByPlayer == dungeon.getRooms()->size());
		}

		TEST_METHOD(PlayerAndMonsterTakeTurns) {
			const Monk player("Monk", "A monk");
			const auto monster = Goblin();
			const Character* currentTurn = &player;
			Assert::IsTrue(currentTurn == &player);
			currentTurn = &monster;
			Assert::IsTrue(currentTurn == &monster);
		}

		TEST_METHOD(PlayerDiesWhenHealthIsZero) {
			Monk player("Monk", "A monk");
			const auto monster = Goblin();
			while (player.getHealthPoints() > 0) {
				monster.attack(player);
			}
			Assert::IsTrue(player.isDead());
		}
	};
}
