#pragma once

#include "Enemy.h"

class Wolf : public Enemy
{
public:
	Wolf();
	virtual void initSkills(const int index) override;

	virtual shared_ptr<Enemy> getType() {
		return make_shared<Wolf>();
	}

};