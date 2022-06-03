
#include "Characters/Archer.h"

Archer::Archer(const sf::Vector2f pos)
	:Player(pos, _archer)
{}

void Archer::initSkills(const int index)
{
	auto base = BaseAttack(BASE_CD, -5, LONG_RANGE, _hp);
	setBaseAttack(base);

}
