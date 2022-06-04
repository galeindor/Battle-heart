#include "Characters/Enemy.h"

Enemy::Enemy(sf::Vector2f pos, const int index)
	: Character(pos, index, characterParams)
{
}

//=======================================================================================
void Enemy::draw(sf::RenderWindow& window)
{
	showHpBar();
	this->getHpBar().draw(window);
	window.draw(this->getSprite());
}

//=======================================================================================

bool Enemy::setTarget(std::shared_ptr<Enemy>) // enemies can't target another enemy - only healer enemy might
{
	return false;
}

//=======================================================================================

bool Enemy::setTarget(std::shared_ptr<Player> obj) // all enemies can target only players
{
	setAsTarget(obj);
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
}
