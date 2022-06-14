#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f pos , int maxValue)
	:m_max(maxValue), m_hitTimer(1.2f) , m_showTimer(3.f)
{
	this->initBars(pos);
	this->initText(pos);
	m_currHealth.setFillColor(sf::Color::Green);
	m_hitHealth.setFillColor(sf::Color::Red);
}

//====================================================================

void HealthBar::updateHealthBar(float statVal, const sf::Vector2f& pos)
{
	this->setPosition(pos);
	auto currSize = m_currHealth.getSize().x;
	auto size = m_bar.getSize();
	statVal = std::min(statVal * BAR_WIDTH / m_max, size.x);
	auto healthLost = currSize - statVal ;

	if (healthLost > 0.f && m_hitTimer.isTimeUp() ) // lowered damage
	{
		m_hitHealth.setSize(sf::Vector2f(currSize, size.y));
		m_hitDamage.setString(std::to_string(int(healthLost)));
		m_hitTimer.setTimer();
	}

	m_showTimer.updateTimer();
	m_hitTimer.updateTimer();

	auto newX = std::max(statVal, 0.f);
	m_currHealth.setSize(sf::Vector2f(newX, size.y));
}

//====================================================================

void HealthBar::initBars(const sf::Vector2f pos)
{
	auto size = sf::Vector2f(BAR_WIDTH, 10);
	auto origin = m_bar.getOrigin();
	m_bar.setOrigin(origin + healthOffset);
	m_bar.setSize(size);
	m_bar.setPosition(pos);
	m_bar.setFillColor(sf::Color::Black);
	m_bar.setOutlineColor(sf::Color::Black);
	m_bar.setOutlineThickness(3);

	m_currHealth = m_hitHealth = m_bar;
}

void HealthBar::draw(sf::RenderWindow& window)
{
	if (!m_showTimer.isTimeUp())
	{
		window.draw(m_bar);
		if (!m_hitTimer.isTimeUp())
		{
			window.draw(m_hitDamage);
			window.draw(m_hitHealth);
			
		}
		window.draw(m_currHealth);
	}
}

//=====================================================================

void HealthBar::setPosition(const sf::Vector2f pos)
{
	m_bar.setPosition(pos);
	m_currHealth.setPosition(pos);
	m_hitHealth.setPosition(pos);
	m_hitDamage.setPosition(pos);
}

//======================================================================

void HealthBar::initText(const sf::Vector2f pos)
{
	m_hitDamage.setCharacterSize(20);
	m_hitDamage.Bold;
	m_hitDamage.setColor(sf::Color::Black);
	m_hitDamage.setFont(*Resources::instance().getFont());
	m_hitDamage.setOrigin(m_hitDamage.getOrigin() + healthTextOffset);
	m_hitDamage.setPosition(pos);
}