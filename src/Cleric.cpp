
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{
	m_sprite.setTexture(*Resources::instance().getTexture(_cleric));

	auto size = m_sprite.getTexture()->getSize();
	m_sprite.setOrigin(size.x/2, size.y/2);
}

void Cleric::hitPlayer()
{
	m_hpBar.lowerHealth(1);
}



