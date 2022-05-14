#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

class HealthBar
{
public:
	HealthBar(sf::Vector2f pos);
	bool lowerHealth(int amount);
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f pos);
	void initHealthBar(const sf::Vector2f pos);
	void initCurrHp(const sf::Vector2f pos);
	int getHp() const { return m_hp; }
private:
	
	int m_hp; // maximum number of hitpoints
	sf::RectangleShape m_bar; 
	sf::RectangleShape m_currHealth;
};
