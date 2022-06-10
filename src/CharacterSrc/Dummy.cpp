#include "Characters/Dummy.h"

Dummy::Dummy()
	:Enemy(_dummy)
{
	this->initSkills(_dummy);
}

void Dummy::initSkills(const int index)
{

	this->createSkill(index, _basic, _damage, singleTarget, onPlayer, !isActive); // basic
}

