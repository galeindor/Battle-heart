
#include "Archer.h"

Archer::Archer(const sf::Vector2f pos)
	:Player(pos, _archer)
{
	initSkills(_archer);
	initStats();
}

void Archer::initSkills(int index)
{
	auto base = BaseAttack(BASE_CD, BASIC_DMG, INFINITY, _hp);
	setBaseAttack(base);

}