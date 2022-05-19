
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{}

//==========================================================

bool Cleric::setTarget(Player& obj) // cleric can get an ally target
{
	this->setAttack(true);
	m_target = (GameObject*)&obj;
	return true;
}
//==========================================================

bool Cleric::setTarget(Enemy& obj) // cleric can't have enemy target
{
	return false;
}
