
#include "Skills/Skill.h"

Skill::Skill(float cooldown, int damage, float range, int wantedStat)
	:m_cooldown(cooldown), m_skillDmg(damage), m_skillRange(range) , m_wantedStat(wantedStat) , m_timeLeft(0)
{}

//==========================================================

Skill::Skill(sf::Texture* texture , const sf::Vector2f& pos ,float cooldown, int damage = BASIC_DMG, float range = 5, int wantedStat=_hp)
	:m_cooldown(cooldown) , m_skillDmg(damage) , m_skillRange(range) , m_timeLeft(0) , m_wantedStat(wantedStat)
{
	m_shape.setTexture(texture);
	m_shape.setPosition(pos);
	m_shape.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE });
	
	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);

}

int Skill::castSkill(Stat stat)
{
	auto copy = stat;
	if (getTimeLeft() <= 0.f)
	{
		copy.handleStat(getDmg());
		setTimeLeft(getCD());
		return copy.getStat();
	}
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
