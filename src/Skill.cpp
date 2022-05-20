
#include "Skill.h"

Skill::Skill(sf::Texture* texture , const sf::Vector2f& pos ,float cooldown)
	:m_cooldown(cooldown) , m_skillDmg(BASIC_DMG) , m_skillRange(5) , m_timeLeft(0)
{
	m_shape.setTexture(texture);
	m_shape.setPosition(pos);
	m_shape.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE });
	
	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);

}

//==========================================================

bool Skill::checkClick(const sf::Vector2f& pos)
{
	return (m_timeLeft == 0.f) && (m_shape.getGlobalBounds().contains(pos));
}

//==========================================================

void Skill::handleClick()
{
	m_timeLeft = m_cooldown;
}

//==========================================================

void Skill::update()
{
	m_timeLeft -= m_clock.restart().asSeconds();

	m_timeLeft = std::max(m_timeLeft, 0.f);

	auto percent = m_timeLeft / m_cooldown;

	m_cooldownScale.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE * percent });
}

//==========================================================

void Skill::draw(sf::RenderWindow& window)
{
	update();
	window.draw(m_shape);
	window.draw(m_cooldownScale);
}
//==========================================================

