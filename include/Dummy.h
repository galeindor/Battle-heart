#pragma once
#include "Enemy.h"

class Dummy : public Enemy
{
public:
	Dummy();
	~Dummy() = default;

protected:
	virtual void initSkills(int index) override;

private:
	sf::Vector2f randEnemyPos() override;
};