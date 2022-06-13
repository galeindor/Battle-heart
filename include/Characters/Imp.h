#pragma once

#include "Enemy.h"

class Imp : public Enemy
{
public:
	Imp();
	virtual shared_ptr<Enemy> getType() {
		return make_shared<Imp>();
	}

	virtual void initSkills(const int index) override;
};