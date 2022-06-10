
#include "Characters/Archer.h"

Archer::Archer(const sf::Vector2f pos)
	:Player(pos, _archer)
{
	this->initSkills(_archer);
}

void Archer::initSkills(const int index)
{
	this->addSkill(Skill(Resources::instance().getSkillText(index, 0),
				  sf::Vector2f(0 * (SKILL_RECT_SIZE + 20) + 30, 30),
				  charactersStats[index][_attackSpeed], _damage, 
			      singleTarget, onPlayer, false));
}
