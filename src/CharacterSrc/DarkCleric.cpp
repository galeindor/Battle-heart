#include "Characters/DarkCleric.h"

DarkCleric::DarkCleric()
	:Enemy(_darkCleric)
{
	this->initSkills(_darkCleric);
	setScale(SPRITE_SCALE);
}

void DarkCleric::initSkills(const int index)
{
	this->createSkill(index, _basic, _heal, AttackType::Multi, !onPlayer, !isActive, _energy); // basic heal on all enemies
}
