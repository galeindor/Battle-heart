#pragma once
#include "macros.h"


class HealthBar
{
public:
	HealthBar(sf::Vector2f pos);
	~HealthBar() = default;
	void updateHealthBar(int statVal);
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f pos);

private:
	void initHealthBar(const sf::Vector2f pos);
	void initCurrHp(const sf::Vector2f pos);
	sf::RectangleShape m_bar;
	sf::RectangleShape m_currHealth;
};
