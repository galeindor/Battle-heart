#include "Skills/Projectile.h"

Projectile::Projectile(float cooldown, const sf::Vector2f pos, const int index)
	: Object(pos, index, projectileParams), m_cooldown(cooldown), m_timeLeft(0)
{}

Projectile::Projectile(sf::Texture* texture, float cooldown, const sf::Vector2f pos, const int index)
	: Object(pos, index, projectileParams), m_cooldown(cooldown), m_timeLeft(0)
{
	m_shape.setTexture(texture);
	m_shape.setPosition(pos);
	m_shape.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE });

	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);
}
