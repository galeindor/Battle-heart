#include "Object.h"

Object::Object(const sf::Vector2f pos, const int index, AnimationParams animParams)

	: m_animation(Resources::instance().getTexture(index), animParams),
	  m_isMoving(false), m_steering(new SteeringInterface), m_velocity(DEFAULT_VEC), m_dest(pos)
{
	this->initSprite(pos, index);
	this->m_target = nullptr;

	// for now
	m_mass = 0.1f;
	m_maxForce = 50;
	m_maxVelocity = 100;
	m_velocity = { 5,5 };
	//m_range = SHORT_RANGE;
}

//=======================================================================================

void Object::handleAnimation(sf::Vector2f movement, float deltaTime)
{
	// If facing right.
	if (movement.x > 0.0f || this->getPosition().x < this->getDest().x)
		this->m_animation.setFaceRight(true);
	else if (movement.x < 0.0f || this->getPosition().x > this->getDest().x)
		this->m_animation.setFaceRight(false);

	this->m_animation.update(deltaTime);
	this->m_sprite.setTextureRect(this->m_animation.getUVRect());
}

//=======================================================================================

void Object::update(const float deltaTime)
{
	handleAnimation( m_velocity * deltaTime, deltaTime);
	this->setPosition(this->adjustLocation(this->getPosition()));

	if (this->getPosition().x < this->m_dest.x)
		this->m_animation.setFaceRight(true);

	else if (this->getPosition().x > this->m_dest.x)
		this->m_animation.setFaceRight(false);
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

void Object::initSprite(const sf::Vector2f pos, const int index)
{
	this->m_sprite.setPosition(pos);
	this->m_sprite.setTexture(*Resources::instance().getTexture(index));
	sf::IntRect size = m_sprite.getTextureRect();
	this->m_sprite.setScale(1.5, 1.5);
	this->m_sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE);
}

//=======================================================================================

bool Object::checkCollision(const sf::Vector2f& location)
{
	return this->m_sprite.getGlobalBounds().contains(location);
}

//=======================================================================================

void Object::initProjectileAnimation(const int index, AnimationParams animParams)
{
	m_animation = Animation(Resources::instance().getProjectile(index), animParams);
}