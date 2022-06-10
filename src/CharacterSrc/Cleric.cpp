
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
	this->createSkill(index, _basic, _heal, singleTarget, onPlayer, !isActive); // basic
	this->createSkill(index, _skill1, _heal, !singleTarget, onPlayer, isActive); // multi heal
	this->createSkill(index, _skill2, _defend, singleTarget, onPlayer, isActive); // shield
}

