
#include "Characters/Archer.h"

Archer::Archer(const sf::Vector2f pos)
	:Player(pos, _archer)
{
	this->initSkills(_archer);
}

void Archer::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, singleTarget, !onPlayer, !isActive , _energy); // basic
	this->createSkill(index, _skill1, _drainLife, singleTarget, !onPlayer, isActive, _tesla ); // aimed shot
	this->createSkill(index, _skill2, _damage, !singleTarget, !onPlayer, isActive , _lightning); // multi hit shot
}
