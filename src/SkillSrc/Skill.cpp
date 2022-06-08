#include "Skills/Skill.h"

#include "Characters/Character.h"

Skill::Skill(sf::Texture* texture, const sf::Vector2f pos, float cooldown,
	const int effectIndex, bool singleTarget, bool onPlayer, bool isActive)
	: m_timer(Timer(cooldown)), m_singleTarget(singleTarget), m_onPlayer(onPlayer), m_isActive(isActive)
{
	m_baseValue = 0;
	this->initRect(texture, pos);
	this->initCooldown(pos);
	this->initEffect(effectIndex);
}

//============================================================================

void Skill::updateSkill(float deltaTime, vector<Character*> targets)
{
	if (!this->m_timer.isTimeUp())
	{
		this->setTargets(targets);
		this->m_timer.updateTimer(deltaTime);

		for (auto i = 0; i < m_projs.size(); i++)
		{
			m_projs[i].update({ 0,0 }, deltaTime);
			if (m_projs[i].checkIntersection())
			{
				//impact here
				m_projs.erase(m_projs.begin() + i);
			}

		}
	}

	for (auto& target : m_targets)
		this->m_effect->update(target->getPosition(), deltaTime, true);
}

//============================================================================

void Skill::useSkill(sf::Vector2f myLoc ,  std::vector<std::shared_ptr<Stat>> myStats)
{
	if (this->m_timer.isTimeUp())
	{
		this->m_timer.setTimer();
		for (auto target : m_targets)
		{
			auto projectile = Projectile(myLoc,target->getPosition(), _healBall, target);
		}
		this->m_effect->affect(m_baseValue, myStats, this->m_targets);
	}
}

//============================================================================

void Skill::initEffect(const int effectIndex)
{
	switch (effectIndex)
	{
	case _heal:
		this->m_effect = new Heal(effectParams);
		break;

	case _damage:
		this->m_effect = new Damage(effectParams);
		break;

	case _defend:
		this->m_effect = new Defend(effectParams);
		break;
	default:
		break;
	}
}

//============================================================================

void Skill::initRect(sf::Texture* texture, const sf::Vector2f pos)
{
	m_rect.setTexture(texture);
	m_rect.setPosition(pos);
	m_rect.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE });
}

//============================================================================

void Skill::initCooldown(const sf::Vector2f pos)
{
	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);
}
