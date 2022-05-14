
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{
	this->getSprite().setTexture(*Resources::instance().getTexture(_cleric));

	auto size = this->getSprite().getTexture()->getSize();
	this->getSprite().setOrigin(size.x/2, size.y/2);
}

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

void Cleric::hitPlayer()
{
	this->getHpBar().lowerHealth(1);
}



