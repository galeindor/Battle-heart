#pragma once

#include "Enemy.h"

class DarkCleric : public Enemy
{
public:
	DarkCleric();
	virtual void initSkills(const int index) override;

	virtual shared_ptr<Enemy> getType() {
		return make_shared<DarkCleric>();
	}

	virtual void update(sf::Vector2f steerForce, const float deltaTime,
		vector<std::shared_ptr<Player>> m_players, vector<std::shared_ptr<Enemy>> m_enemies) override;

private:

	std::shared_ptr<Enemy> findMostInjured(vector<std::shared_ptr<Enemy>> m_enemies);
};