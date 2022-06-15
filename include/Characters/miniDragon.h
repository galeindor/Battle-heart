#pragma once

#include "Enemy.h"

class MiniDragon : public Enemy
{
public:
	MiniDragon();
	virtual void initSkills(const int index) override;

	virtual shared_ptr<Enemy> getType() {
		return make_shared<MiniDragon>();
	}

};