
#include "Skills/Projectile.h"
#include "Characters/Character.h"

Projectile::Projectile(const sf::Vector2f pos, const sf::Vector2f dest, const int index , std::shared_ptr<Character> target)
	:Object(pos, index, projectileParams)
{

	setAsTarget(target);

	setDestination(dest);
}

//==============================================================================

bool Projectile::checkIntersection() const
{
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	auto epsilon = 10.f;
	return norm <= epsilon;
}
//==============================================================================
Animation Projectile::initAnimation(const int index, AnimationParams animParams)
{
	return Animation(Resources::instance().getProjectile(index), animParams);
}

//==============================================================================
void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}