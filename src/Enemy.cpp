#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, const int index)
	: GameObject(pos, index)
{}

//=======================================================================================
void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}

void Enemy::updateMovement(const float deltaTime)
{
	bool moving = true;

	if (this->moveValidator() && !this->checkIntersection())
		this->move(deltaTime);
	else
		moving = false;

	this->setMovement(moving);
}

//=======================================================================================
bool Enemy::setTarget(Enemy& obj) // enemies can't target another enemy - only healer enemy might
{
	return false;
}

//=======================================================================================
bool Enemy::setTarget(Player& obj) // all enemies can target only players
{
	m_target = (GameObject*)&obj;
	return true;
}