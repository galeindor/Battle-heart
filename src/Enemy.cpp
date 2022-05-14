#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos)
	: GameObject(pos, ENEMY_POS)
{}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}


void Enemy::update(const float deltaTime)
{
	this->updateMovement(deltaTime);
	
}