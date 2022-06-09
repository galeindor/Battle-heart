
#include "Characters/Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos , _knight)
{
	this->initSkills(_knight); //nadav the king
}

void Knight::initSkills(const int index)
{
	this->addSkill(Skill(Resources::instance().getSkill(index, 0),
		sf::Vector2f(0 * (SKILL_RECT_SIZE + 20) + 30, 30),
		playersBasicStats[index][_attackSpeed], _damage,
		singleTarget, onPlayer, isActive));
}

