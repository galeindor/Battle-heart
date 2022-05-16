
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{
	this->getSprite().setTexture(*Resources::instance().getTexture(_cleric));

	auto size = this->getSprite().getTexture()->getSize();
	this->getSprite().setOrigin(size.x/2, size.y/2);
}

//==========================================================

void Cleric::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}

void Cleric::handleCollision(Dummy& dummy)
{
}

void Cleric::handleCollision(Cleric& cleric)
{
}

void Cleric::handleColiision(Knight& knight)
{

}

//==========================================================

bool Cleric::setTarget(Player& obj) // cleric can get an ally target
{
	m_target = (GameObject*)&obj;
	return true;
}
//==========================================================

bool Cleric::setTarget(Enemy& obj) // cleric can't have enemy target
{
	return false;
}
