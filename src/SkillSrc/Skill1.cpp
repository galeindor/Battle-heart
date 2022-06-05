#include "Skills/Skill1.h"
Skill1::Skill1(sf::Texture* texture, const sf::Vector2f pos, float cooldown, 
			   const int effectIndex, bool singleTarget, bool onPlayer)
	:	m_cooldown(cooldown), m_timeLeft(0), m_singleTarget(singleTarget), m_onPlayer(onPlayer)
{
	this->initRect(texture, pos);
	this->initCooldown(pos);
	this->initEffect(effectIndex);
}

void Skill1::updateSkill(const float deltaTime, std::vector<Target> targets)
{
	if (this->m_timeLeft >= 0)
	{
		this->setTargets(targets);
		this->m_timeLeft -= this->m_clock.restart().asSeconds();

		//this->m_effect->update()
	}

	for (auto& target : this->m_targets)
		this->m_effect->update(target._location, deltaTime, true);
}

void Skill1::useSkill(std::vector<std::shared_ptr<Stat>> myStats)
{
	if (this->m_timeLeft <= 0)
	{
		this->m_timeLeft = m_cooldown;
		this->m_effect->affect(myStats, this->m_targets);
	}
}

void Skill1::initEffect(const int effectIndex)
{
	switch (effectIndex)
	{
	case _heal:
		this->m_effect = new Heal(effectParams);
		break;

	default:
		break;
	}
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
