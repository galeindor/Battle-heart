#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f pos , int maxValue)
	:m_max(maxValue),m_curr(maxValue), m_showTimer(3.f)
{
	this->initBars(pos);
	//this->initText(pos);
}

//====================================================================
// Updating health's bar position and hp amount 
void HealthBar::updateHealthBar(float statVal, const sf::Vector2f& pos)
{
	this->setPosition(pos);
	auto size = m_bar.getSize();

	statVal = std::min(statVal, m_max); // health can not be more than m_max
	auto healthLost = m_curr - statVal ;
	
	
	if (healthLost > 0.f )
	{
		addDamageText(true, healthLost, pos);
		m_hitUI.back()._hitRect.setSize({m_curr * BAR_WIDTH / m_max , size.y });
	}
	else if (healthLost < 0.f)
	{
		addDamageText(false, -healthLost, pos );
		m_hitUI.back()._hitRect.setSize({statVal * BAR_WIDTH / m_max , size.y });
	}

	m_curr = statVal; // update current hp to be the new Stat

	m_showTimer.updateTimer();
	for (auto i = 0 ;i < m_hitUI.size(); i++)
	{
		m_hitUI[i]._timer.updateTimer();
		if (m_hitUI[i]._timer.isTimeUp())
		{
			m_hitUI.erase(m_hitUI.begin() + i);
			i--;
		}
	}

	auto newX = std::max(statVal * BAR_WIDTH / m_max , 0.f);
	m_currHealth.setSize(sf::Vector2f(newX, size.y));
}

//====================================================================

void HealthBar::addDamageText(bool lostHP, float amount, const sf::Vector2f& pos)
{
	auto offset = sf::Vector2f(10.f, 0.f);
	auto color = lostHP? sf::Color::Red : sf::Color::Green;
	auto DamageText = sf::Text();
	DamageText.setString(std::to_string(int(std::ceil(amount))));
	DamageText.setFillColor(color);
	auto hit = HitUI();
	hit._text = DamageText;
	hit._hitRect = m_currHealth;
	hit._hitRect.setFillColor(color);
	hit._hitRect.setPosition(pos + offset * float(m_hitUI.size()));
	hit._timer.setTimer();
	this->initText(hit._text, pos);
	m_hitUI.push_back(hit);
	m_hitUI.back()._text.setFillColor(color);
}

//====================================================================


// init size and colours of the bars 
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

	m_currHealth = m_bar;
	m_currHealth.setFillColor(sf::Color::Green);
}

//====================================================================

void HealthBar::draw(sf::RenderWindow& window)
{
	if (!m_showTimer.isTimeUp()) // show hp bar only if show() has been actived
	{
		window.draw(m_bar);
		for (auto& hit : m_hitUI)
			if (!hit._timer.isTimeUp()) // show hit bar if got hit / healed
			{
				window.draw(hit._hitRect);
				window.draw(hit._text);
			}
		window.draw(m_currHealth);
	}
}

//=====================================================================
// move the health bar to follow the target ( move to position)
void HealthBar::setPosition(const sf::Vector2f pos)
{
	m_bar.setPosition(pos);
	m_currHealth.setPosition(pos);
	for (auto& hit : m_hitUI)
	{
		hit._hitRect.setPosition(pos);
		hit._text.setPosition(pos);
	}
}

//======================================================================
// init text stats , font , size and etc.
void HealthBar::initText(sf::Text& text, const sf::Vector2f pos)
{
	text.setCharacterSize(20);
	text.setOutlineThickness(2);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Black);
	text.setFont(*Resources::instance().getFont());
	text.setOrigin(m_bar.getOrigin() + healthTextOffset);
	text.setPosition(pos);
}