
#include "Skills/BasicAttack.h"

BaseAttack::BaseAttack(float cooldown, int damage, float range, int wanted)
	:Skill(cooldown,damage,range , wanted), m_effect(new Effect(sf::Vector2f(5, 1), 0.3f, _heal))
{}

//==========================================================

int BaseAttack::castSkill(Stat stat)
{
	auto copy = stat;
	if (getTimeLeft() <= 0.f)
	{
		copy.handleStat(getDmg());
		setTimeLeft(getCD());
		return copy.getStat();
	}
	return 0;
}

void BaseAttack::updateBasic(const sf::Vector2f pos, const float deltaTime, bool faceRight)
{
	this->m_effect->update(pos, deltaTime, faceRight);
}

void BaseAttack::affectWithBasic()
{
	this->m_effect->affect();
}

void BaseAttack::drawEffect(sf::RenderWindow& window)
{
	this->m_effect->draw(window);
}

//==========================================================