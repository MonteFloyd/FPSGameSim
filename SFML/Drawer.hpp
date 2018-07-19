#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Drawer
{
public:
	//Player* player;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	//std::shared_ptr<sf::Vector2f> currentPosition;
	sf::Vector2f& currentPosition;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update();
	Drawer(sf::Vector2f& pos);
	//template<typename T>
	void Attach(sf::Vector2f & pos);
	//void Link(Player * player);
	~Drawer();
};

