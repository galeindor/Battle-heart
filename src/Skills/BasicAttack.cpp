
#include "includeSkill/BasicAttack.h"

BaseAttack::BaseAttack(float cooldown, int damage, float range, int wanted)
	:Skill(cooldown,damage,range , wanted)
{}

//==========================================================

int BaseAttack::castSkill(Stat stat)
{
	auto copy = stat;
	if (getTimeLeft() <= 0.f)
	{
		copy.handleStat(getDmg());
		setTimeLeft(getCD());
		return copy.getStat();
	}
	return 0;
}

//==========================================================