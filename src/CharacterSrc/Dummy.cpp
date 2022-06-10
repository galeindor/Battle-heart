#include "Characters/Dummy.h"

Dummy::Dummy()
	:Enemy(_dummy)
{
	this->initSkills(_dummy);
}

void Dummy::initSkills(const int index)
{
	this->addSkill(Skill(Resources::instance().getSkill(index, 0),
		sf::Vector2f(0 * (SKILL_RECT_SIZE + 20) + 30, 30),
		playersBasicStats[index][_attackSpeed], _damage,
		singleTarget, onPlayer, !isActive,1.f));
}

