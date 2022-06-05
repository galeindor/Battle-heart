#include "Characters/Enemy.h"

Enemy::Enemy(sf::Vector2f pos, const int index)
	: Character(pos, index, characterParams)
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

	//return (std::abs(this->getPosition().x - this->getDest().x) < epsilon || std::abs(this->getPosition().y - this->getDest().y) < epsilon);
	//int dx = this->getSprite().getPosition().x - this->getDest().x;
	//int dy = this->getSprite().getPosition().y - this->getDest().y;
	//float d3 = (dx * dx) + (dy * dy);
	//float d = sqrt(d3);

	//if (d < 60)
	//	return true;

	//return false;
}

void Enemy::initSkills(const int index)
{
	this->addSkill(Skill1(Resources::instance().getSkill(index, 0),
		sf::Vector2f(0 * (SKILL_RECT_SIZE + 20) + 30, 30),
		BASE_CD, _heal, singleTarget, onPlayer));
}
