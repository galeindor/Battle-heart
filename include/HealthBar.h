#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

class HealthBar
{
public:
	HealthBar(sf::Vector2f pos);
	bool lowerHealth(int amount);
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f newLoc);

private:

	int m_hp; // maximum number of hitpoints
	sf::RectangleShape m_bar; 
	sf::RectangleShape m_currHealth;

};
