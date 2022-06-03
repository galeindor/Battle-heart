
#include "Characters/Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{}

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
	auto base = BaseAttack(BASE_CD, -5, LONG_RANGE, _hp);
	setBaseAttack(base);

}
