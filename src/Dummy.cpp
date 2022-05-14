#include "Dummy.h"

Dummy::Dummy()
	: Enemy(this->randEnemyPos())
{
	this->getSprite().setTexture(*Resources::instance().getTexture(_dummy));
	this->getSprite().setScale(0.3, 0.3);
	sf::Vector2f temp;
}

sf::Vector2f Dummy::randEnemyPos() 
{
	//return sf::Vector2f{ 400,400 };
	
	sf::Vector2f pos;
	int side = rand();
	bool left = (side % 2 == 0) ? true : false;
	if (left)
		pos.x = 0; //adjust
	else
		pos.x = WINDOW_WIDTH; //adjust

	pos.y = rand() % WINDOW_HEIGHT;
	return pos;
}