#pragma once

#include "Resources.h"
#include "HealthBar.h"

class Player
{
public:
	Player(const sf::Vector2f loc);

	sf::Vector2f getPosition() const;
	void draw(sf::RenderWindow& window);

	bool moveValidator(sf::Vector2f dest);
	void movePlayer(sf::Vector2f direction, float delta);
	bool checkCollision(sf::Vector2f loc);

protected:
	sf::Vector2f m_loc;
	sf::Sprite m_sprite;
	HealthBar m_hpBar;
};