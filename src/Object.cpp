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
	m_maxForce = 1;
	m_maxVelocity = 80;
	m_range = SHORT_RANGE;
}

//=======================================================================================

void Object::handleAnimation(sf::Vector2f movement, float deltaTime)
{
	// If facing right.
	if (movement.x > 0.0f)
		this->m_faceRight = true;
	else if (movement.x < 0.0f)
		this->m_faceRight = false;

	this->m_animation.update(this->m_row, deltaTime, this->m_faceRight);
	this->m_sprite.setTextureRect(this->m_animation.getUVRect());
}

//=======================================================================================

void Object::update(sf::Vector2f steerForce, const float deltaTime)
{
	sf::Vector2f acceleration = steerForce / this->m_mass;
	this->m_velocity = this->m_velocity + acceleration * deltaTime;
	this->m_velocity = this->m_steering->Truncate(this->m_velocity, this->m_maxVelocity);


	if (!this->checkIntersection())
	{
		this->m_isMoving = true;
		this->getSprite().move(this->m_velocity * deltaTime);
		this->m_row = _walk;
	}
	else
	{
		this->m_isMoving = false;
		this->m_row = _idle;

		//if (targetInRange())
		{ }
			//useBaseAttack();
	}

	// Trim position values to window size and handle animation
	this->handleAnimation(this->m_velocity * deltaTime, deltaTime);
	this->getSprite().setPosition(this->adjustLocation(this->getSprite().getPosition()));
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
