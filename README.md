# FPSGameSim
SFML and C++ based 2D shooting game simulation.

### Current Work

You need SFML libraries to run this project, you can find it and more information [here](https://www.sfml-dev.org/index.php) .

This is still work in progress however it currently has, Navigation Graph and Pathfinding system and Vision/LOS system. Aim for the future is implementing better AI and teamwork through a combination of offline and online planning algorithms.

### Features

#### Navigation
Uses graph fill to fill in the 2D Map with nodes and uses A* to find a path when needed.

![AStar](https://github.com/MonteFloyd/FPSGameSim/blob/master/gifs/sfml2.gif)


#### Vision/LOS

Simple raycasting.

![Raycast](https://raw.githubusercontent.com/MonteFloyd/FPSGameSim/master/gifs/sfml1.gif)



