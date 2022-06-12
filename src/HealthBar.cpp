#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f pos , int maxValue)
	:m_max(maxValue), m_hitTimer(1.8f) , m_showTimer(3.f)
{
	this->initCurrHp(pos);
	this->initHitHp(pos);
	this->initHealthBar(pos);
}

//====================================================================

void HealthBar::updateHealthBar(float statVal)
{
	auto currSize = m_currHealth.getSize().x;
	auto size = m_bar.getSize();
	statVal = std::min(statVal * BAR_WIDTH / m_max, size.x);
	//auto healthLost = statVal- currSize ;
	auto healthLost = currSize - statVal ;

	if (healthLost > 0.f && m_hitTimer.isTimeUp() ) // lowered damage
	{
		m_hitHealth.setSize(sf::Vector2f(currSize, size.y));
		m_hitTimer.setTimer();
	}

	m_showTimer.updateTimer();
	m_hitTimer.updateTimer();

	auto newX = std::max(statVal, 0.f);
	m_currHealth.setSize(sf::Vector2f(newX, size.y));
}

//====================================================================

void HealthBar::initHealthBar(const sf::Vector2f pos)
{
	auto size = sf::Vector2f(BAR_WIDTH, 10);
	auto origin = m_bar.getOrigin();
	m_bar.setOrigin(origin + healthOffset);
	m_bar.setSize(size);
	m_bar.setPosition(pos);
	m_bar.setFillColor(sf::Color::Black);
	m_bar.setOutlineColor(sf::Color::Black);
	m_bar.setOutlineThickness(3);
}

//====================================================================

void HealthBar::initCurrHp(const sf::Vector2f pos)
{
	auto size = sf::Vector2f(BAR_WIDTH, 10);
	auto origin = m_bar.getOrigin();
	m_currHealth.setOrigin((origin + healthOffset));
	m_currHealth.setSize(size);
	m_currHealth.setPosition(pos);
	m_currHealth.setFillColor(sf::Color::Green);
	m_currHealth.setOutlineColor(sf::Color::Black);
	m_currHealth.setOutlineThickness(2);
}

//====================================================================

void HealthBar::initHitHp(const sf::Vector2f pos)
{
	auto size = sf::Vector2f(BAR_WIDTH, 10);
	auto origin = m_bar.getOrigin();
	m_hitHealth.setOrigin(origin + healthOffset);
	m_hitHealth.setSize(size);
	m_hitHealth.setPosition(pos);
	m_hitHealth.setFillColor(sf::Color::Red);
	m_hitHealth.setOutlineColor(sf::Color::Black);
	m_hitHealth.setOutlineThickness(3);
}


//====================================================================

void HealthBar::draw(sf::RenderWindow& window)
{
	if (!m_showTimer.isTimeUp())
	{
		window.draw(m_bar);
		if (!m_hitTimer.isTimeUp())
			window.draw(m_hitHealth);
		window.draw(m_currHealth);
	}
}

//=====================================================================

void HealthBar::setPosition(const sf::Vector2f pos)
{
	m_bar.setPosition(pos);
	m_currHealth.setPosition(pos);
	m_hitHealth.setPosition(pos);
}


