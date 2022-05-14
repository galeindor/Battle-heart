#include "Dummy.h"

Dummy::Dummy()
	: Enemy(this->randEnemyPos())
{
	this->getSprite().setTexture(*Resources::instance().getTexture(_dummy));
	this->getSprite().setScale(0.3, 0.3);
}

void Dummy::handleCollision(GameObject& object)
{
	if (&object == this) return;
	object.handleCollision(*this);
}

void Dummy::handleCollision(Dummy& dummy)
{
	if (&dummy == this) return;
	dummy.handleCollision(*this);
}

void Dummy::handleCollision(Cleric& cleric)
{
	this->setAttack(true);
	cleric.handleCollision(*this);
}

void Dummy::handleColiision(Knight& knight)
{
	this->setAttack(true);
	knight.handleCollision(*this);
}

sf::Vector2f Dummy::randEnemyPos()
{
	sf::Vector2f pos;
	int side = rand();
	bool left = (side % 2 == 0) ? true : false;
	if (left)
		pos.x = 0; //adjust
	else
		pos.x = WINDOW_WIDTH; //adjust

	pos.y = rand() % WINDOW_HEIGHT;
	return pos;
}