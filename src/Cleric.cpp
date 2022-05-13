
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{
	this->getSprite().setTexture(*Resources::instance().getTexture(_cleric));

	auto size = this->getSprite().getTexture()->getSize();
	this->getSprite().setOrigin(size.x/2, size.y/2);
}

void Cleric::hitPlayer()
{
	this->getHpBar().lowerHealth(1);
}



