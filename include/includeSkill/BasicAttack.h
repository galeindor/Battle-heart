#pragma once

#include "includeSkill/Skill.h"

class BaseAttack : public Skill
{
public:
	BaseAttack(float cooldown, int damage, float range);
	~BaseAttack() = default;

	virtual int castSkill(Stat stat) override;

private:

};