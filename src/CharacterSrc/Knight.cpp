
#include "Characters/Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos , _knight)
{
	this->initSkills(_knight); //nadav the king
}

void Knight::initSkills(const int index)
{
	int i = 0;

	// create(
	this->addSkill(Skill(Resources::instance().getSkill(index, i), // basic
		sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
		skillCooldowns[index][i], _damage,
		singleTarget, !onPlayer, !isActive,1));
	i++;
	this->addSkill(Skill(Resources::instance().getSkill(index, i), // shield skill
		sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
		skillCooldowns[index][i], _defend,
		singleTarget, !onPlayer, isActive,1.5f));
	i++;
	this->addSkill(Skill(Resources::instance().getSkill(index, i), // intimidate
		sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
		skillCooldowns[index][i], _damage,
		singleTarget, !onPlayer, isActive,1));
	


}

