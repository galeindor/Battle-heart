#pragma once
#include "Resources.h"
#include "Timer.h"
#include <utility>

struct HitUI
{
	sf::Text _text;
	Timer _timer = Timer(0.8f);
	sf::RectangleShape _hitRect;
};

class HealthBar
{
public:
	// C-tors and d-tor.
	HealthBar() :m_showTimer(3.f), m_max(100), m_curr(100){}
	HealthBar(sf::Vector2f pos, int maxValue);
	~HealthBar() = default;

	// Management and visuals.
	void updateHealthBar(float statVal, const sf::Vector2f& pos);
	void draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f pos);
	void show() { m_showTimer.setTimer(); }

private:
	// Initiation functions.
	void initBars(const sf::Vector2f pos);
	void initText(sf::Text& text, const sf::Vector2f pos);
	void addDamageText(bool lostHP, float amount, const sf::Vector2f& pos);

	// Visuals.
	sf::RectangleShape m_bar;
	sf::RectangleShape m_currHealth;
	vector<HitUI> m_hitUI;

	// Mangement.
	float m_max;
	float m_curr;
	Timer m_showTimer;

};
