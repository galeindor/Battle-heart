
#include "Characters/Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{
	this->initSkills(_cleric);
}

//==========================================================

bool Cleric::setTarget(std::shared_ptr<Player> obj) // cleric can get an ally target
{
	this->setAttacking(true);
	setAsTarget(obj); 
	return true;
}
//==========================================================

bool Cleric::setTarget(std::shared_ptr<Enemy>) // cleric can't have enemy target
{
	return false;
}

void Cleric::initSkills(const int index)
{
	int i = 0;
	this->addSkill(Skill(Resources::instance().getSkillText(index, i), // build basic skill
						sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
						skillCooldowns[index][i], _heal,
						singleTarget, onPlayer, !isActive, 1.f));
	i++;
	this->addSkill(Skill(Resources::instance().getSkillText(index, i), // build multi heal skill
						sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
						skillCooldowns[index][i], _heal,
						!singleTarget, onPlayer, isActive , 1.75f));
	i++;
}

