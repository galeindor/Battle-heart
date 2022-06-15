#include "Characters/Wolf.h"

Wolf::Wolf()
	:Enemy(_wolf)
{
	this->initSkills(_wolf);
	setScale(SPRITE_SCALE);
}

void Wolf::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single, onPlayer, !isActive, _none); // basic
}
