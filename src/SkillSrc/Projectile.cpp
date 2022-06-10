
#include "Skills/Projectile.h"
#include "Characters/Character.h"

Projectile::Projectile(const sf::Vector2f pos, const sf::Vector2f dest, const int index , std::shared_ptr<Character> target)
	:Object(pos, index, projectileParams)
{
	setAsTarget(target);
	
	setDestination(dest);

	this->setVelocity({5, 5});
}

//==============================================================================

bool Projectile::checkIntersection() const
{
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	auto epsilon = 10.f;
	return norm <= epsilon;
}

//==============================================================================
void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}

//==============================================================================
void Projectile::updateProjectile(float deltaTime)
{
	Object::update(deltaTime);
	setAnimation(0);
	handleAnimation(this->getVelocity() * deltaTime, deltaTime);
	this->setDestination(this->getTarget()->getPosition());
	/*
	sf::Vector2f acceleration = steerForce / this->getMass();
	this->setVelocity(this->getVelocity() + acceleration * deltaTime); 
	this->setVelocity(this->behaviour()->Truncate(this->getVelocity(), this->getMaxVelocity()));
	
	*/
	auto dir = this->getPosition() - this->getDest();
	dir = -dir;
	auto speed = 1.1f;
	this->setPosition(this->getPosition()+ speed * dir * deltaTime);
}