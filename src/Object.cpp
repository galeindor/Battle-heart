#include "Object.h"

Object::Object(const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime)
	: m_animation(Resources::instance().getTexture(index), imageCount, switchTime), 
	  m_isMoving(false), m_steering(new SteeringInterface), m_row(0), m_faceRight(true), 
	  m_velocity(DEFAULT_VEC), m_dest(pos)
{
	this->m_sprite.setPosition(pos);
	m_sprite.setTexture(*Resources::instance().getTexture(index));
	sf::IntRect size = m_sprite.getTextureRect();
	this->m_sprite.setScale(1.5, 1.5);
	m_sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE);

	// for now
	m_mass = 0.1f;
	m_maxForce = 50;
	m_maxVelocity = 100;
	m_range = SHORT_RANGE;
}

//=======================================================================================

void Object::handleAnimation(sf::Vector2f movement, float deltaTime)
{
	// If facing right.
	if (movement.x > 0.0f || this->getPosition().x < this->getDest().x)
		this->m_faceRight = true;
	else if (movement.x < 0.0f || this->getPosition().x > this->getDest().x)
		this->m_faceRight = false;

	this->m_animation.update(this->m_row, deltaTime, this->m_faceRight);
	this->m_sprite.setTextureRect(this->m_animation.getUVRect());
}

void Object::update(sf::Vector2f steerForce, const float deltaTime)
{
	this->handleAnimation(this->m_velocity * deltaTime, deltaTime);
	this->setPosition(this->adjustLocation(this->getPosition()));
}

//=======================================================================================

sf::Vector2f Object::adjustLocation(sf::Vector2f location)
{
	auto newLoc = sf::Vector2f();
	newLoc.x = std::min(location.x, float(WINDOW_WIDTH - CUT_CORNERS));
	newLoc.y = std::min(location.y, float(WINDOW_HEIGHT - 1.5f * CUT_CORNERS));

	newLoc.x = std::max(newLoc.x, float(CUT_CORNERS));
	newLoc.y = std::max(newLoc.y, float(HEIGHT_LIMIT));

	return newLoc;
}

//=======================================================================================

bool Object::checkCollision(const sf::Vector2f& location)
{
	return this->m_sprite.getGlobalBounds().contains(location);
}

//=======================================================================================
