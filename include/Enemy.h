#pragma once
#include "GameObject.h"
#include "Knight.h"
#include "Cleric.h"

class Enemy : public GameObject
{
public:
	Enemy(sf::Vector2f enemy);
	void draw(sf::RenderWindow& window) override;
	void update(const float deltaTime) override;
	
private:
	virtual sf::Vector2f randEnemyPos() = 0;
};