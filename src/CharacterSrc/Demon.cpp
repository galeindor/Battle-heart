#include "Characters/Demon.h"

Demon::Demon()
	:Enemy(_demon)
{
	this->initSkills(_demon);
	this->setOffset(DemonOffset);
}

//================================================================

void Demon::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single, onPlayer, !isActive, _none); // basic
}
