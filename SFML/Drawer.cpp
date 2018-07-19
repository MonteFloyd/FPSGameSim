#include "Drawer.hpp"
#include <iostream>


void Drawer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(playerSprite, states);
}

void Drawer::Update() {
	playerSprite.setPosition(currentPosition);
}

Drawer::Drawer(sf::Vector2f& pos) : currentPosition(pos)
{
	if (!playerTexture.loadFromFile("playerIdle.png")) {
		std::cout << "cant read player texture \n";
	}

	playerSprite.setTexture(playerTexture);

}

void Drawer::Attach(sf::Vector2f& pos) {
	playerSprite.setPosition(pos);

}

Drawer::~Drawer()
{
}
