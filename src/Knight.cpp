
#include "Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos)
{
	m_sprite.setTexture(*Resources::instance().getTexture(_knight));

	auto size = m_sprite.getTexture()->getSize();
	m_sprite.setOrigin(size.x / 2 -15 , size.y / 2);

}