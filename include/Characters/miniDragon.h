#pragma once

#include "Enemy.h"

class miniDragon : public Enemy
{
public:
	miniDragon();
	virtual shared_ptr<Enemy> getType() {
		return make_shared<miniDragon>();
	}

	virtual void initSkills(const int index) override;
};