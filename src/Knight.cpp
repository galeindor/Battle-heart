
#include "Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos , _knight)
{
	this->getSprite().setTexture(*Resources::instance().getTexture(_knight));
	auto size = this->getSprite().getTexture()->getSize();
	this->getSprite().setOrigin(size.x / 2 -15 , size.y / 2 - 5);

}

void Knight::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}

void Knight::handleCollision(Dummy& dummy)
{
	this->setAttack(true);
	this->setDestination(this->getSprite().getPosition());
}

void Knight::handleCollision(Cleric& cleric)
{}//nothing to do here rly

void Knight::handleColiision(Knight& knight)
{}//wont happend
