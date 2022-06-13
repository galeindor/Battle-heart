#pragma once
#include "Object.h"
#define RAD2DEG (180.0f / (float)PI)

class Character;

class Projectile : public Object
{
public:
	Projectile(const sf::Vector2f pos, const sf::Vector2f dest , 
			   const int index, std::shared_ptr<Character> target);
	
	virtual bool checkIntersection() const override;

	void draw(sf::RenderWindow& window);
	void updateProjectile(sf::Vector2f steerForce,float deltaTime);

private:
	float m_orientation;
};

