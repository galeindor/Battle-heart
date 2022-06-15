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

};