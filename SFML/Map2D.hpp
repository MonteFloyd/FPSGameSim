#pragma once
#ifndef MAP_HPP	
#define MAP_HPP

#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "VectorUtil.hpp"


class Node {

public:
	Node() {};
	Node(int x, int y) : posX(x), posY(y), pos((float)x, (float)y) {};

	Node(sf::Vector2f newPos,int index_) : posX(newPos.x), posY(newPos.y), pos(newPos),index(index_) {};
	int index;
	int posX;
	int posY;

	sf::Vector2f pos;

	

};

class Edge {

public:

	int cost;
	int from;
	sf::Vector2f fromPos;
	sf::Vector2f toPos;
	int to;

	Edge() {};
	Edge(int from_, int to_,sf::Vector2f fromPos_, sf::Vector2f toPos_, int cost_) : 
		cost(cost_),
		from(from_),
		fromPos(fromPos_),	
		toPos(toPos_),
		to(to_) {};

};

class Wall : sf::Drawable {
public:
	sf::Vector2f A;
	sf::Vector2f B;
	sf::Vector2f C;
	sf::Vector2f D;
	Wall(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) : A(a), B(b), C(c),D(d) {  };

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;




};

class NavigationGraph {
public:

	std::vector<Node> nodesList;
	//std::vector< std::vector<Node> > nodeVec;
	std::vector< std::vector<Edge> > edgeList;
	int Height;
	int Width;
	float tileWidth;
	float tileHeight;
	int numofTilesX;
	int numofTilesY;
	std::vector<int> path;
	std::vector<sf::Vector2f> finalPath;
	//int currIndex;

	void addNode(const Node& node) { nodesList.push_back(node); };
	int getIndexfromPos(sf::Vector2f pos) { }
	void setWidth(int width_) { Width = width_; }
	void setHeight(int height_) { Height = height_; }
	int PosToIndex(float x, float y);
	void addEdges(int row,int col);
	//void AStar(NavigationGraph & graph, sf::Vector2f source, sf::Vector2f target);
	void setMaxY(int maxY) { numofTilesY = maxY; }
	void setMaxX(int maxX) { numofTilesX = maxX; }

	void AStar(sf::Vector2f source, sf::Vector2f target);

};

class Map2D : public sf::Drawable {
public:

	NavigationGraph navGraph;

	std::vector< sf::Vector2f > nodes;

	std::vector< Wall > walls;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getClosestWallIntersect(sf::Vector2f A, sf::Vector2f B, float & distance, sf::Vector2f & intersection);

	void clearEdges();

	void addWall(sf::Vector2f a, sf::Vector2f b,sf::Vector2f c, sf::Vector2f d );

	void addNode(const sf::Vector2f & node);

	//const sf::Drawable& popDrawable();

	void buildGraph(int mapWidth, int mapHeight, int tileX, int tileY);

	void removeInvalidEdges();


};

#endif
