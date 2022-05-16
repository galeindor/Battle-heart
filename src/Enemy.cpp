#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos)
	: GameObject(pos, ENEMY_POS)
{}

//=======================================================================================
void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}

//=======================================================================================
void Enemy::update(const float deltaTime)
{
	this->updateMovement(deltaTime);
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