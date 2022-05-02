
#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f pos)
	:m_hp(MAX_HEALTH)
{
	auto size = sf::Vector2f(BAR_WIDTH, 15);
	auto origin = m_bar.getOrigin();

	m_bar.setOrigin(origin.x + 30 , origin.y + 70);
	m_currHealth.setOrigin(sf::Vector2f(origin.x + 30 , origin.y + 70 ));

	m_bar.setSize(size);
	m_currHealth.setSize(size);

	m_bar.setPosition(pos);
	m_currHealth.setPosition(pos);

	m_bar.setFillColor(sf::Color::Black);
	m_bar.setOutlineColor(sf::Color::Black);
	m_bar.setOutlineThickness(3);
	m_currHealth.setFillColor(sf::Color::Green);
	m_currHealth.setOutlineColor(sf::Color::Black);
	m_currHealth.setOutlineThickness(2);
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

void HealthBar::setPosition(const sf::Vector2f newLoc)
{
	m_bar.setPosition(newLoc);
	m_currHealth.setPosition(newLoc);
}