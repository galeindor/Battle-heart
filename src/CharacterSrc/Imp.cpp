#include "Characters/Imp.h"

Imp::Imp()
	:Enemy(_imp)
{
	this->initSkills(_imp);
}

void Imp::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, singleTarget, onPlayer, !isActive, _fireProj); // basic
}
