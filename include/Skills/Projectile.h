#pragma once
#include "Object.h"

class Character;

class Projectile : public Object
{
public:
	Projectile(const sf::Vector2f pos, const sf::Vector2f dest , const int index, Character* target);
	~Projectile() = default;
	
	virtual bool checkIntersection() const override;

private:
};

