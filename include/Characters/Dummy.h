#pragma once
#include "Enemy.h"

class Dummy : public Enemy
{
public:
	Dummy();
	~Dummy() = default;
	virtual shared_ptr<Enemy> getType() {
		return make_shared<Dummy>();
	}
};