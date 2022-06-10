
#include "Characters/Archer.h"

Archer::Archer(const sf::Vector2f pos)
	:Player(pos, _archer)
{
	this->initSkills(_archer);
}

void Archer::initSkills(const int index)
{
	
	this->createSkill(index, _basic, _damage, singleTarget, !onPlayer, !isActive); // basic
	this->createSkill(index, _skill1, _drainLife, singleTarget, !onPlayer, isActive); // aimed shot
	this->createSkill(index, _skill2, _damage, !singleTarget, !onPlayer, isActive); // multi hit shot

	/*
	this->addSkill(Skill(Resources::instance().getSkill(index, i),
					sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
					skillCooldowns[index][i], _damage, 
					singleTarget, !onPlayer, !isActive,1));
	

	this->addSkill(Skill(Resources::instance().getSkill(index, i), // big boy shot
					sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
					skillCooldowns[index][i], _damage,
					singleTarget, !onPlayer, isActive, 1.3f));
	i++
	this->addSkill(Skill(Resources::instance().getSkill(index, i), // multi target shot
					sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30),
					skillCooldowns[index][i], _damage,
					!singleTarget, !onPlayer, isActive, 1.3f));
	i++;
	*/
}
