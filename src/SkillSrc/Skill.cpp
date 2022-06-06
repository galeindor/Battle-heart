#include "Skills/Skill.h"

Skill::Skill(sf::Texture* texture, const sf::Vector2f pos, float cooldown, 
			   const int effectIndex, bool singleTarget, bool onPlayer, bool isActive)
	:	m_timer(Timer(cooldown)), m_singleTarget(singleTarget), m_onPlayer(onPlayer), m_isActive(isActive)
{
	this->initRect(texture, pos);
	this->initCooldown(pos);
	this->initEffect(effectIndex);
}

void Skill::updateSkill(const float deltaTime, std::vector<Target> targets)
{
	if (!this->m_timer.isTimeUp())
	{
		this->setTargets(targets);
		this->m_timer.updateTimer(deltaTime);

		//this->m_effect->update()
	}

	for (auto& target : this->m_targets)
		this->m_effect->update(target._location, deltaTime, true);
}

void Skill::useSkill(std::vector<std::shared_ptr<Stat>> myStats)
{
	if (this->m_timer.isTimeUp())
	{
		this->m_timer.setTimer();
		this->m_effect->affect(myStats, this->m_targets);
	}
}

void Skill::initEffect(const int effectIndex)
{
	switch (effectIndex)
	{
	case _heal:
		this->m_effect = new Heal(effectParams);
		break;

	case _dmg:
		this->m_effect = new Damage(effectParams);
		break;

	default:
		break;
	}
}

void Skill::initRect(sf::Texture* texture, const sf::Vector2f pos)
{
	m_rect.setTexture(texture);
	m_rect.setPosition(pos);
	m_rect.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE });
}

void Skill::initCooldown(const sf::Vector2f pos)
{
	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);
}
