#pragma once
#include "Enemy.h"

class Dummy : public Enemy
{
public:
	Dummy();
	virtual shared_ptr<Enemy> getType() {
		return make_shared<Dummy>();
	}

	virtual void initSkills(const int index) override;
};