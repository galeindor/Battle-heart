#pragma once

#include "ClericSkill.h"

class Heal : public ClericSkill
{
public:
	using ClericSkill::ClericSkill;

private:
	virtual int castSkill(Stat stat) override;
};