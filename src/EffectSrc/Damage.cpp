#include "Effects/Damage.h"

Damage::Damage(AnimationParams animParams)
	: Effect(_damage)
{}

void Damage::affect(vector<std::shared_ptr<Stat>> myStats, std::vector<Target> targets)
{
	for (auto& target : targets)
	{
		auto currHP = target._stats[_hp]->getStat();
		target._stats[_hp]->setStat(currHP - myStats[_dmg]->getStat());
	}
}
