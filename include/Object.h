#pragma once

#include "Animation.h"
#include "Resources.h"
#include "SteeringInterface.h"
class SteeringInterface;
class Character;

class Object
{
public:
	Object(const sf::Vector2f pos, const int index, AnimationParams animParams);
	virtual ~Object() = default;

	// Management
	bool handleAnimation(sf::Vector2f movement, float deltaTime);
	void update(const float deltaTime);

	// Virtuals
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
	Character* getTarget()			const { return this->m_target.get(); }
	bool getFaceRight()				const { return this->m_animation.getFaceRight(); }
	
	//check
	void setFaceRight(bool faceRight) { this->m_animation.setFaceRight(faceRight); }
	// Setters
	void setDestination(sf::Vector2f dest) { this->m_dest = adjustLocation(dest); }
	void setMoving(bool movement) { this->m_isMoving = movement; }
	void setVelocity(sf::Vector2f velocity) { this->m_velocity = velocity; }
	void setPosition(sf::Vector2f pos) { this->m_sprite.setPosition(pos); }
	void setAsTarget(std::shared_ptr<Character> obj) { this->m_target = obj; }
	void setAnimation(int index) { this->m_animation.setRow(index); }

	// Checks/validators
	bool checkCollision(const sf::Vector2f& location);
	sf::Vector2f adjustLocation(sf::Vector2f location);

protected:
	void setRange(float val)				{ m_range = val; }
	void setScale(sf::Vector2f scale)		{ m_sprite.setScale(scale); }
	void setOrigin(sf::Vector2f origin)		{ m_sprite.setOrigin(origin); }
private:
	void initSprite(const sf::Vector2f pos, const int index);

	// General
	sf::Sprite m_sprite;
	bool m_isMoving;
	std::shared_ptr<Character> m_target;

	// For animation.
	Animation m_animation;

	// For movement.
	SteeringInterface* m_steering;
	sf::Vector2f m_velocity;
	sf::Vector2f m_dest;
	float m_mass;
	float m_maxForce;
	float m_maxVelocity;
	float m_range;
};