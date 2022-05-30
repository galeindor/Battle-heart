#include "includeSkill/ShieldBuff.h"

int ShieldBuff::castSkill(Stat stat)
{
	auto copy = stat;
	if (getTimeLeft() <= 0.f)
	{
		copy.handleStat(getDmg());
		setTimeLeft(getCD());
		return copy.getStat();
	}
}
