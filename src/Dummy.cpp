#include "Dummy.h"

Dummy::Dummy()
	:Enemy(this->randEnemyPos(), _dummy)
{
	initSkills(_dummy);
	initStats();
}

//==========================================================

sf::Vector2f Dummy::randEnemyPos()
{
	sf::Vector2f pos;
	int side = rand();
	bool left = (side % 2 == 0) ? true : false;
	if (left)
		pos.x = 0; //adjust
	else
		pos.x = WINDOW_WIDTH; //adjust

	pos.y = (rand() % (WINDOW_HEIGHT - HEIGHT_LIMIT)) + HEIGHT_LIMIT;
	return pos;
}

//==========================================================

void Dummy::initSkills(int index)
{
	auto base = BaseAttack(BASE_CD, BASIC_DMG , SHORT_RANGE , _hp);
	setBaseAttack(base);

}