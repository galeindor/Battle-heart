
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos)
{
	m_sprite.setTexture(*Resources::instance().getTexture(_cleric));

	auto size = m_sprite.getTexture()->getSize();
	m_sprite.setOrigin(size.x/2, size.y/2);
}


/*
void Cleric::draw(sf::RenderWindow& window)
{
	m_hpBar.draw(window);
	window.draw(m_sprite);
}
*/

void Cleric::hitPlayer()
{
	m_hpBar.lowerHealth(1);
}

bool Cleric::handleCollision(sf::Vector2f location)
{
	return m_sprite.getGlobalBounds().contains(location);
}