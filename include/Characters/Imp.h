#pragma once
#include "Enemy.h"

// This class is in charge of the imp enemy.
class Imp : public Enemy
{
public:
	Imp();
	virtual shared_ptr<Enemy> getType() {
		return make_shared<Imp>();
	}
	virtual void initSkills(const int index) override;
};