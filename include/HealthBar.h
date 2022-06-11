#pragma once
#include "macros.h"
#include "Timer.h"

class HealthBar
{
public:
	HealthBar() :m_showTimer(3.f) ,m_hitTimer(0.8f) , m_max(100){}
	HealthBar(sf::Vector2f pos, int maxValue);
	~HealthBar() = default;
	void updateHealthBar(float statVal);
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f pos);
	void show() { m_showTimer.setTimer(); }

private:
	void initHealthBar(const sf::Vector2f pos);
	void initHitHp(const sf::Vector2f pos);
	void initCurrHp(const sf::Vector2f pos);
	sf::RectangleShape m_bar;
	sf::RectangleShape m_currHealth;
	sf::RectangleShape m_hitHealth;
	int m_max;
	// show Hp for a few seconds
	Timer m_showTimer;
	Timer m_hitTimer;
};
