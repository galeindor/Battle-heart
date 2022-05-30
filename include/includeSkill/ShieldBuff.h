#pragma once

#include "includeSkill/ClericSkill.h"

class ShieldBuff : public ClericSkill
{
public:
	using ClericSkill::ClericSkill;

private:
	virtual int castSkill(Stat stat) override;
};