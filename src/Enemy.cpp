#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, const int index)
	: GameObject(pos, index, sf::Vector2f(9, 5), 0.3f)
{}

//=======================================================================================
void Enemy::draw(sf::RenderWindow& window)
{
	this->getHpBar().draw(window);
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
	int dx = this->getSprite().getPosition().x - this->getDest().x;
	int dy = this->getSprite().getPosition().y - this->getDest().y;
	float d3 = (dx * dx) + (dy * dy);
	float d = sqrt(d3);

	if (d < 60)
		return true;

	return false;

	/*
	if (this->getTarget())
		return this->getSprite().getGlobalBounds().intersects(this->getTarget()->getSprite().getGlobalBounds());

	return false;
	*/
}
