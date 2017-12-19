# Mediocre 3D Engine

This is my initial stab at a 3D engine in C++.  It uses SFML, OpenGL, Boost, and GLM.  This seems to work on my mac with no guarantees elsewhere.

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
git clone https://github.com/raygun321/graphy.git
```

## Modules

* common

Code used across projects that didn't make it in the engine

* engine

The work in progress 3d engine.

* cube

An example showing a cube.

* irrlicht

An attempt a using irrlicht. I'm not sure this works.

* springs

2D graph-spring example using SFML

* springs3d

3D version on the graph spring code using the engine.

* triangle

Basic triangle example

* Tutorial

An evolving example using parts of the engine. Currently displays a rotating textured model loaded from an OBJ file.
