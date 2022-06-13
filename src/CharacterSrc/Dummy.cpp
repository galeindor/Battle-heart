#include "Characters/Dummy.h"

Dummy::Dummy()
	:Enemy(_demon)
{
	this->initSkills(_demon);
}

void Dummy::initSkills(const int index)
{

	this->createSkill(index, _basic, _damage, singleTarget, onPlayer, !isActive, _none); // basic
}
