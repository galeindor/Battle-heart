#pragma once
#include "Enemy.h"

class Dummy : public Enemy
{
public:
	Dummy();
	~Dummy() = default;
	void handleCollision(GameObject& object) override;
	void handleCollision(Dummy& dummy) override;
	void handleCollision(Cleric& cleric) override;
	void handleColiision(Knight& knight) override;
private:
	sf::Vector2f randEnemyPos() override;
};