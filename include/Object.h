#pragma once

#include "Animation.h"
#include "Resources.h"
#include "SteeringInterface.h"
class SteeringInterface;
class Character;

class Object
{
public:
	Object(const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime);
	virtual ~Object() = default;

	// Virtuals
	virtual void handleAnimation(sf::Vector2f movement, float deltaTime);
	virtual void update(sf::Vector2f steerForce, const float deltaTime);
	virtual bool checkIntersection() const = 0;

	// Getters
	sf::Sprite getSprite()		    const { return this->m_sprite; }
	sf::FloatRect getGlobalBounds() const { return m_sprite.getGlobalBounds(); }
	sf::Vector2f getPosition()		const { return this->m_sprite.getPosition(); }
	sf::Vector2f getVelocity()		const { return this->m_velocity; }
	float getMaxVelocity()			const { return this->m_maxVelocity; }
	float getMaxForce()				const { return this->m_maxForce; }
	SteeringInterface* behaviour()	const { return this->m_steering; }
	sf::Vector2f	getDest()		const { return this->m_dest; }
	bool getIsMoving()				const { return this->m_isMoving; }
	float getRange()				const { return this->m_range; }
	float getMass()					const { return this->m_mass; }

	// Setters
	void setDestination(sf::Vector2f dest) { this->m_dest = adjustLocation(dest); }
	void setRow(ObjectAnimation index) { this->m_row = int(index); }
	void setMoving(bool movement) { this->m_isMoving = movement; }
	void setVelocity(sf::Vector2f velocity) { this->m_velocity = velocity; }
	void setPosition(sf::Vector2f pos) { this->m_sprite.setPosition(pos); }

	// Checks/validators
	bool checkCollision(const sf::Vector2f& location);
	sf::Vector2f adjustLocation(sf::Vector2f location);

private:
	
	// General
	sf::Sprite m_sprite;
	bool m_isMoving;

	// For animation.
	Animation m_animation;
	unsigned int m_row;
	bool m_faceRight;

	// For movement.
	SteeringInterface* m_steering;
	sf::Vector2f m_velocity;
	sf::Vector2f m_dest;
	float m_mass;
	float m_maxForce;
	float m_maxVelocity;
	float m_range;
};