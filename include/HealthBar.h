#pragma once
#include "macros.h"
#include "Resources.h"
#include "Timer.h"

class HealthBar
{
public:
	HealthBar() :m_showTimer(3.f) ,m_hitTimer(0.8f) , m_max(100){}
	HealthBar(sf::Vector2f pos, int maxValue);
	~HealthBar() = default;
	void updateHealthBar(float statVal, const sf::Vector2f& pos);
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f pos);
	void show() { m_showTimer.setTimer(); }

private:
	void initBars(const sf::Vector2f pos);
	void initText(const sf::Vector2f pos);

	sf::RectangleShape m_bar;
	sf::RectangleShape m_currHealth;
	sf::RectangleShape m_hitHealth;
	
	sf::Text m_hitDamage;
	float m_max;
	float m_curr;
	// show Hp for a few seconds
	Timer m_showTimer;
	Timer m_hitTimer;
};
