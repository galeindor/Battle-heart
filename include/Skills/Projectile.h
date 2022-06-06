#pragma once
#include "Object.h"

class Character;

class Projectile : public Object
{
public:
	Projectile(const sf::Vector2f pos, const int index);
	~Projectile() = default;
};

