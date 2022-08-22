#include "Characters/Dragon.h"

// Constructor.
Dragon::Dragon()
	:Enemy(_Dragon)
{
	this->initSkills(_Dragon);
	this->setOffset({ 10,-20 });
}

// Inits skills.
void Dragon::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single , onPlayer, !isActive, _fireBreath); // basic
}
