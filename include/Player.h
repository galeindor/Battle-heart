#pragma once

#include "Resources.h"
#include "HealthBar.h"

class Player
{
public:
	Player(const sf::Vector2f loc);

	sf::Vector2f getPosition() const;
	void draw(sf::RenderWindow& window);
	bool checkCollision(sf::Vector2f loc);
	bool moveValidator();

	void updatePlayer(float deltaTime);
	void movePlayer(float deltaTime);
	void setDestination(sf::Vector2f dest) { this->m_dest = dest; }
	bool getIsMoving() const { return this->m_isMoving; }
protected:
	bool m_isMoving;
	sf::Vector2f m_dest;
	sf::Sprite m_sprite;
	HealthBar m_hpBar;
};