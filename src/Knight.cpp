
#include "Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos , _knight)
{
	initSkills(_knight);
	initStats();
}

void Knight::initSkills(int index)
{
	auto base = BaseAttack(BASE_CD, BASIC_DMG , SHORT_RANGE, _hp);
	setBaseAttack(base);

	int i = 0;
}