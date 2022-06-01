#pragma once
#include "Enemy.h"

class Dummy : public Enemy
{
public:
	Dummy();
	~Dummy() = default;

private:
	virtual sf::Vector2f randEnemyPos() override;
};