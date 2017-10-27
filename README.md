# Shitty Dungeon Generator

This is my initial stab at a dungeon generator in C++.  It uses sfml.  I'm doing most of my work on a mac, you might want totoo.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

[SFML](https://www.sfml-dev.org/)
[Catch](https://github.com/philsquared/Catch) (this is bundled with the project)

OSX:

```
brew install sfml
```

Ubuntu
```
sudo apt-get install libsfml-dev
```

### Installing

* Clone the repository

```
git clone git@bitbucket.org:joecodemonkey/dungeon.git
```

* Build the unit tests
```
cd dungeon
./mac_tests.sh
```

* Build the generator
```
./mac_build.sh
./dungen
```

## Classes

### Vector2

This is the template for the vectors I'm using to represent every location in the dungeon.   The squares in the dungeon are Vector2i (integer), but distances are measured in Vector2d (double)

### Tile

This is the lowest level of the dungeon.  Every square in a dungeon is a tile.  I could have used polymorphism here, but I thought it was overkill.

### Dungeon

Basically a vector of vector of Tiles.  I'm thinking more and more of the dungeon should live in the DungeonFactory which creates the dungeon.  Eventually, the dungeon should contain the state for the game (all items, mobs, etc in the dungeon)

###  Room

The idea was that room would be a class representing a room in the dungeon.  Now I'm starting to think it will be part of DungeonFactory only b/c we never care about room again after the dungeon has been generated.  I haven't moved it yet though as I'm not sure.

###  DungeonFactory

This is the magical dungeon generator.  It's a work in progress.  I've got rooms being generated, but digging tunnels is making me question my choices in life.  I'm getting there though.  


### Utility

A catch all with static methods that exists primarily to keep me from filling like a sloppy asshole.


### Future Classes

* DungeonMaster - This class would own the game loop.  I just like the name though as it makes me feel clever.

* Player - This is the player's class (Class as in C++, not as in Fighter/Mage).  I've not thought it out much.

* Monster - 
