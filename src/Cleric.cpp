
#include "Cleric.h"

Cleric::Cleric(const sf::Vector2f pos)
	:Player(pos , _cleric)
{}

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

//==========================================================

void Cleric::initSkills(int index)
{
	auto base = BaseAttack(2.f, -BASIC_DMG, INFINITY, _hp);
	setBaseAttack(base);

	for (int i = 0; i < MAX_SKILL; i++)
	{
		auto skill = Skill(Resources::instance().getSkill(index, i), sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30), ATK_CD, BASIC_DMG, 5.f, _hp);
		addSkill(skill);
	}
}
