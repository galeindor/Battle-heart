
#include "Characters/Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos , _knight)
{
	this->initSkills(_knight);
}

void Knight::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, singleTarget, !onPlayer, !isActive,_none); // basic
	this->createSkill(index, _skill1, _damage, singleTarget, onPlayer, isActive,_none); // shield wall
	this->createSkill(index, _skill2, _damage, singleTarget, !onPlayer, isActive, _none); // intimidate
}

