
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{}

//==========================================================

bool Cleric::setTarget(Player& obj) // cleric can get an ally target
{
	this->setAttacking(true);
	setAsTarget((GameObject*)&obj); 
	return true;
}
//==========================================================

bool Cleric::setTarget(Enemy&) // cleric can't have enemy target
{
	return false;
}
