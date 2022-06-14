
#include "Characters/Witch.h"

Witch::Witch(const sf::Vector2f pos)
	:Player(pos, _witch)
{
	this->initSkills(_witch);
}

void Witch::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, singleTarget, !onPlayer, !isActive , _energy); // basic
	this->createSkill(index, _skill1, _drainLife, singleTarget, !onPlayer, isActive, _tesla ); // aimed shot
	this->createSkill(index, _skill2, _damage, !singleTarget, !onPlayer, isActive , _lightning); // multi hit shot
}
