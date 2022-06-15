#pragma once
#include "Enemy.h"

class Demon : public Enemy
{
public:
	Demon();
	virtual shared_ptr<Enemy> getType() {
		return make_shared<Demon>();
	}

	virtual void initSkills(const int index) override;
};