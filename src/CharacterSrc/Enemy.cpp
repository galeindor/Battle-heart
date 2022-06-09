#include "Characters/Enemy.h"

//==========================================================

Enemy::Enemy(const int index)
	: Character(this->randEnemyPos(), index, characterParams)
{

}

//=======================================================================================
void Enemy::draw(sf::RenderWindow& window)
{
	showHpBar();
	drawSkills(window);
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
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	return (norm <= this->getStat(_range));
}

//=======================================================================================

//=======================================================================================

sf::Vector2f Enemy::randEnemyPos()
{
	sf::Vector2f pos;
	int side = rand();
	bool left = (side % 2 == 0) ? true : false;
	if (left)
		pos.x = 0; //adjust
	else
		pos.x = WINDOW_WIDTH; //adjust

	pos.y = (rand() % (WINDOW_HEIGHT - HEIGHT_LIMIT)) + HEIGHT_LIMIT;
	return pos;
}

//=======================================================================================
