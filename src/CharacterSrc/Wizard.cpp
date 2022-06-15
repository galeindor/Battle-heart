
#include "Characters/Wizard.h"

// Constructor.
Wizard::Wizard(const sf::Vector2f pos)
	:Player(pos, _wizard)
{
	this->initSkills(_wizard);
}

// Inits skills.
void Wizard::initSkills(const int index)
{
	this->createSkill(index, _basic, _damage, AttackType::Single, !onPlayer, !isActive , _energy); // basic
	this->createSkill(index, _skill1, _drainLife, AttackType::Single, !onPlayer, isActive, _tesla ); // aimed shot
	this->createSkill(index, _skill2, _damage, AttackType::Multi, !onPlayer, isActive , _lightning); // multi hit shot
}
