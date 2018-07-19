#pragma once

#include "Pathfinder2D.hpp"
#include "Drawer.hpp"
//#include "Map2D.hpp"
#include <string>

	
class Player {
public:
	Pathfinder2D myPathfinder;
	Drawer myDrawer;
	//PlayerStateManager stateManager;
	//PlayerDecisionMaker decisionMaker;
	
	std::string playerName;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Vector2f currentPosition;

	Player(NavigationGraph& graph);
	void Move(sf::Vector2f target);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f newPos) { currentPosition = newPos; }
	void setGraph(NavigationGraph& graph) { myPathfinder.setGraph(graph); }
	sf::Vector2f getPosition() { return currentPosition; }
	void Update();
	//void Update();

};
