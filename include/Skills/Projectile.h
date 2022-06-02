#pragma once
#include "Object.h"
#include "Domain.h"
class Character;

class Projectile : public Object
{
public:
	Projectile(sf::Texture* texture, float cooldown, const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime);
	Projectile(float cooldown, const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime);
	~Projectile() = default;

private:
	sf::Clock m_clock;
	float m_cooldown;
	float m_timeLeft;

	// skill visual part
	sf::RectangleShape m_shape;
	sf::RectangleShape m_cooldownScale;
};

