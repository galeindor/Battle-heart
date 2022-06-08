#pragma once
#include "Object.h"

class Character;

class Projectile : public Object
{
public:
	Projectile(const sf::Vector2f pos, const sf::Vector2f dest , const int index, std::shared_ptr<Character> target);
	~Projectile() = default;
	
	virtual bool checkIntersection() const override;

	void draw(sf::RenderWindow& window);

protected:
	virtual Animation initAnimation(const int index, AnimationParams animParams) override;
};

