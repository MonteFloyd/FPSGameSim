#pragma once
#ifndef PATHFINDER_2D_HPP
#define PATHFINDER_2D_HPP

//#include <memory>
#include "Map2D.hpp"


class Pathfinder2D {
public:
	NavigationGraph graph;
	//Player* player;

	bool stillSearching;
	float speed;
	bool stillMoving;
	std::vector<int> path;
	std::vector<sf::Vector2f> VecPath;
	sf::Vector2f moveDirection;
	sf::Vector2f& currentPosition;

	void vec2DNormalize(sf::Vector2f & vec);

	Pathfinder2D(sf::Vector2f& position);
	//Pathfinder2D(NavigationGraph& graph_,sf::Vector2f& currPos_);
	~Pathfinder2D();
	void Move(sf::Vector2f target);
	void Update();
	void setPath(std::vector<sf::Vector2f> path_);
	bool AStar(sf::Vector2f source, sf::Vector2f target);
	void setGraph(NavigationGraph& graph_) { graph = graph_; }
	//void setPos(sf::Vector2f& posRef) { currentPosition = posRef; }
	void Attach(sf::Vector2f &pos) { currentPosition = pos; }


	//void  moveUpdate();
	void stop();
};

#endif