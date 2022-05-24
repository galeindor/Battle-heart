
#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f pos)
	: m_hp(MAX_HEALTH)
{
	this->initCurrHp(pos);
	this->initHealthBar(pos);
}

//====================================================================

bool HealthBar::lowerHealth(int amount)
{
	auto size = m_bar.getSize();
	
	m_hp -= amount;
 
	double newX = double(std::max(m_hp, 0) * BAR_WIDTH / MAX_HEALTH) ;
	m_currHealth.setSize(sf::Vector2f( newX , size.y ));

	return (m_hp > 0);
}

//====================================================================

void HealthBar::draw(sf::RenderWindow& window)
{
	window.draw(m_bar);
	window.draw(m_currHealth);
}

//=====================================================================

void HealthBar::setPosition(const sf::Vector2f pos)
{
	m_bar.setPosition(pos);
	m_currHealth.setPosition(pos);
}

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
