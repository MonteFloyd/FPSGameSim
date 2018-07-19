#include "Player.hpp"
#include <iostream>

Player::Player(NavigationGraph& graph_) : myPathfinder(currentPosition), myDrawer(currentPosition)
{
	playerName = "test";
	setGraph(graph_);

}



void Player::Move(sf::Vector2f target) 
{
	myPathfinder.Move(target);

}

void Player::Update() {
	myPathfinder.Update();
	myDrawer.Update();
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	myDrawer.draw(target,states);

}
