#include "Characters/Enemy.h"

//==========================================================

Enemy::Enemy(const int index)
	: Character(this->randEnemyPos(), index, characterParams)
{
	this->initSkills(index);
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
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	return (norm <= this->getStat(_range));
}

//=======================================================================================

void Enemy::initSkills(const int index)
{
	this->addSkill(Skill(Resources::instance().getSkillText(index, 0),
		sf::Vector2f(0 * (SKILL_RECT_SIZE + 20) + 30, 30),
		BASE_CD, _heal, singleTarget, onPlayer, isActive));

}

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
