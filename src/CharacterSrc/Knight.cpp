
#include "Characters/Knight.h"

Knight::Knight(const sf::Vector2f pos)
	:Player(pos , _knight)
{}

void Knight::initSkills(const int index)
{
	auto base = BaseAttack(BASE_CD, -5, SHORT_RANGE, _hp);
	setBaseAttack(base);
}
