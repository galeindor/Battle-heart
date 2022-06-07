#pragma once
#include "macros.h"


class HealthBar
{
public:
	HealthBar() :m_showTime(3) {}
	HealthBar(sf::Vector2f pos, int maxValue);
	~HealthBar() = default;
	void updateHealthBar(int statVal);
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f pos);
	void show() { m_showTime = 3.f; }

private:
	void initHealthBar(const sf::Vector2f pos);
	void initCurrHp(const sf::Vector2f pos);
	sf::RectangleShape m_bar;
	sf::RectangleShape m_currHealth;
	int m_max;
	// show Hp for a few seconds
	sf::Clock m_clock;
	float m_showTime;
};
