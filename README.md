
# Monk Game - Object-Oriented Systems Development
## Project Aim
In the broadest sense, you are required to design and develop a working prototype of a simple, low-cost, yet highly scalable dungeon exploration Monk game using C++. It will enable a single player to explore a dungeon with varying rooms, engage in combat against computer-controlled monsters and upon completion of the
dungeon, loot treasure.  
The prototype software game will consist of the following two components:
1. A dungeon generation feature that should be able to randomly generate dungeons to be explored during the game.
2. An exploration feature that allows the controlled Monk to explore the dungeon and fight against monsters.

The detailed specification of these two components is for you to derive based on the following information which cannot be changed.

## Dungeon Generation Component
A dungeon is characterised by a set of rooms, that are connected to each other so that the Monk can move between them.
1. Your prototype must be able to generate three types of rooms: empty room, monster room, upgrade room and the treasure room. There can be only one treasure room in a dungeon, but there may be multiple empty, upgrade and monster rooms.
2. Each room is described by its type, and by the rooms, it is connected to. Each room has to be connected to at least one other room.
3. As you don’t have the budget to design and craft a set of monsters manually, the dungeon generation component is generating a single type of monster: a goblin with 10 health points, and 2 attack points.  
For testing your prototype, your generation component must be able to generate a dungeon with at least five rooms, one treasure room, one empty rooms, one upgrade room and two monster room.  
The Monk has to be positioned in one room and must be able to visit all the rooms and to reach the treasure to finish the game.

## Exploration Component
The exploration component allows the Monk to explore the rooms of the dungeon.
1. At the start of the game, the player is required to personalise the Monk by providing a name, and a short description and the Monk is positioned in a room of the dungeon. The Monk has 15 health points and 3 attack points.
2. The Monk can move between two rooms, but only if they are connected.
3. In an empty room, the Monk can pray to restore his health points fully.
4. An upgrade Room allows the player to increase their maximum health points by 5 or increase their attack points by 2.
5. When entering a monster room, the Monk has to fight.
a. A fight is turn-based combat. In each turn, the player and the automatically controlled monster can select the action to perform from 2 possible actions. An action has a 50% chance of failure. This has to be properly simulated in the video game.
i. Attack: this reduces the health points of the other fighter by the amount of “attack points” of the attacker.
ii. Defend: the fighter recovers one health point.
6) During the exploration, information about the visited rooms, the performed actions, and the combats must be shown on screen. The information displayed must include the visited rooms and their type; in case of a fight, for each turn it must display: the health points of the Monk and the monster, and the actions each of them performed.
7) The exploration ends when the Monk reaches the treasure room, or he is defeated (reaches 0 or fewer health points) in combat