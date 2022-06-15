#include "Characters/MiniDragon.h"

// Constructor.
MiniDragon::MiniDragon()
	:Enemy(_MiniDragon)
{
	this->initSkills(_MiniDragon);
	this->setOffset({ 10,-20 });
}

// Inits skills.
void MiniDragon::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single , onPlayer, !isActive, _fireBreath); // basic
}
