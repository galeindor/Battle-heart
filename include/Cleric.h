#pragma once

#include "Resources.h"
#include "Player.h"

class Cleric : public Player
{
public:
	Cleric(const sf::Vector2f pos);
	~Cleric() = default;
	
	//void draw(sf::RenderWindow& window);

	bool handleCollision(sf::Vector2f loc);

	void hitPlayer();

private:

};