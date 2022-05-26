
#include "includeSkill/BasicAttack.h"

BaseAttack::BaseAttack(float cooldown, int damage, float range)
	:Skill(cooldown,damage,range)
{}

//==========================================================

int BaseAttack::castSkill(Stat stat)
{
	auto copy = stat;
	if (getTimeLeft() <= 0.f)
	{
		stat.handleStat(getDmg());
		setTimeLeft(getCD());
		return stat.getStat();
	}
}
//==========================================================