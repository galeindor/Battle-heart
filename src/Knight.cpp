
#include "Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos , _knight)
{
	this->getSprite().setTexture(*Resources::instance().getTexture(_knight));
	auto size = this->getSprite().getTexture()->getSize();
	this->getSprite().setOrigin(size.x / 2 -15 , size.y / 2 - 5);

}