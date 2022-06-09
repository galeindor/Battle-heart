
#include "Characters/Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{
	this->initSkills(_cleric);
}

//==========================================================

bool Cleric::setTarget(std::shared_ptr<Player> obj) // cleric can get an ally target
{
	this->setAttacking(true);
	setAsTarget(obj); 
	return true;
}
//==========================================================

bool Cleric::setTarget(std::shared_ptr<Enemy>) // cleric can't have enemy target
{
	return false;
}

void Cleric::initSkills(const int index)
{
	this->addSkill(Skill(Resources::instance().getSkill(index, 0),
			  sf::Vector2f(0 * (SKILL_RECT_SIZE + 20) + 30, 30),
			  playersBasicStats[index][_attackSpeed], _heal, 
			  singleTarget, onPlayer, isActive));
}

