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

void Enemy::updateMovement(const float deltaTime)
{
	bool moving = true;

	this->m_prevPosition = this->getSprite().getPosition();

	if (this->moveValidator() && !this->checkIntersection())
		this->move(deltaTime);
	else
		moving = false;

	this->setMoving(moving);
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

void Enemy::handleCollision(Enemy& enemy)
{
	if (&enemy == this) return;
	this->orbitAround();
}

void Enemy::orbitAround()
{
	float theta = std::atan2(this->m_prevPosition.y - this->getTarget()->getPosition().y, this->m_prevPosition.x - this->getTarget()->getPosition().x) * (180 / 3.141f);
	//normalised so 0 is up
	theta +=40;

	if (theta < 0)
	{
		theta += 360;
	}
	else if (theta > 360)
	{
		theta -= 360;
	}

	sf::Vector2f newDest;
	newDest.x = this->getTarget()->getPosition().x + (400 * std::cos(theta * (3.141f / 180)));
	newDest.y = this->getTarget()->getPosition().y + (400 * std::sin(theta * (3.141f / 180)));
	this->setDestination(newDest);
}
