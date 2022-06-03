#include "Skills/Skill1.h"
Skill1::Skill1(std::vector<Target> domain, sf::Texture* texture, const sf::Vector2f pos, 
			   float cooldown, int value, const int effectIndex)
	:	m_cooldown(cooldown), m_skillVal(value), m_timeLeft(0),
		m_effect(new Effect(effectIndex))
{
	this->initRect(texture, pos);
	this->initCooldown(pos);
}

void Skill1::updateSkill(const float deltaTime)
{
	this->m_effect->affect(this->m_domain->getTargets());
}

void Skill1::initRect(sf::Texture* texture, const sf::Vector2f pos)
{
	m_rect.setTexture(texture);
	m_rect.setPosition(pos);
	m_rect.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE });
}

void Skill1::initCooldown(const sf::Vector2f pos)
{
	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);
}
