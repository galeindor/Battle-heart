#include "Dummy.h"

Dummy::Dummy()
	:Enemy(this->randEnemyPos(), _dummy)
{}

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