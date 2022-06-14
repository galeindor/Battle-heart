#include "Characters/MiniDragon.h"

MiniDragon::MiniDragon()
	:Enemy(_MiniDragon)
{
	this->initSkills(_MiniDragon);
	this->setOffset({ 10,-20 });
}

void MiniDragon::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single , onPlayer, !isActive, _fireBreath); // basic
}
