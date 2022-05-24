#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, const int index)
	: GameObject(pos, index)
{}

//=======================================================================================
void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}

//=======================================================================================

bool Enemy::setTarget(Enemy&) // enemies can't target another enemy - only healer enemy might
{
	return false;
}

//=======================================================================================

bool Enemy::setTarget(Player& obj) // all enemies can target only players
{
	setAsTarget((GameObject*)&obj);
	return true;
}

//=======================================================================================

bool Enemy::checkIntersection() const
{
	if (this->getTarget())
		return this->getSprite().getGlobalBounds().intersects(this->getTarget()->getSprite().getGlobalBounds());

	return false;
}
