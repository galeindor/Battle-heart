#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f pos , int maxValue)
	:m_max(maxValue),m_curr(maxValue), m_hitTimer(1.2f) , m_showTimer(3.f)
{
	this->initBars(pos);
	this->initText(pos);
	m_currHealth.setFillColor(sf::Color::Green);
	m_hitHealth.setFillColor(sf::Color::Red);
}

//====================================================================
// Updating health's bar position and hp amount 
void HealthBar::updateHealthBar(float statVal, const sf::Vector2f& pos)
{
	this->setPosition(pos);
	auto size = m_bar.getSize();
	auto healthLost = m_curr - statVal ;
	auto temp = statVal;
	statVal = std::min(statVal * BAR_WIDTH / m_max, size.x);
	
	if (healthLost > 0.f && m_hitTimer.isTimeUp() ) 
	{
		m_hitDamage.setFillColor(sf::Color::Red);
		m_hitDamage.setString(std::to_string(int(std::ceil(healthLost))));
		m_hitHealth.setSize({m_curr * BAR_WIDTH / m_max , size.y });
		m_hitTimer.setTimer();
	}
	else if (healthLost < 0.f)
	{
		m_hitDamage.setFillColor(sf::Color::Green);
		m_hitDamage.setString(std::to_string(int(std::floor(-healthLost))));
		m_hitHealth.setSize({statVal, size.y });
		m_hitTimer.setTimer();
	}
	m_curr = temp;

	m_showTimer.updateTimer();
	m_hitTimer.updateTimer();
	auto newX = std::max(statVal, 0.f);
	m_currHealth.setSize(sf::Vector2f(newX, size.y));
}

//====================================================================

void HealthBar::initBars(const sf::Vector2f pos)
{
	auto size = sf::Vector2f(BAR_WIDTH, BAR_HEIGHT);
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
	m_hitDamage.setOutlineThickness(2);
	m_hitDamage.setStyle(sf::Text::Bold);
	m_hitDamage.setColor(sf::Color::Black);
	m_hitDamage.setFont(*Resources::instance().getFont());
	m_hitDamage.setOrigin(m_hitDamage.getOrigin() + healthTextOffset);
	m_hitDamage.setPosition(pos);
}