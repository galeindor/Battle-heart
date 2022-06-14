#pragma once

#include "Enemy.h"

class MiniDragon : public Enemy
{
public:
	MiniDragon();
	virtual shared_ptr<Enemy> getType() {
		return make_shared<MiniDragon>();
	}

	virtual void initSkills(const int index) override;
};