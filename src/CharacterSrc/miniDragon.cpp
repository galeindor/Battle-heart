#include "Characters/miniDragon.h"

miniDragon::miniDragon()
	:Enemy(_miniDragon)
{
	this->initSkills(_miniDragon);
	this->setOffset({ 10,-20 });
}

void miniDragon::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, singleTarget, onPlayer, !isActive, _fireProj); // basic
}
