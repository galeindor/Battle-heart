#pragma once

#include "Projectile.h"
#include "Skills/Skill1.h"

class Active : public Skill1
{
public:
	Active();
	~Active() = default;
private:
	Projectile* projectile;
};