#include "Effects/Heal.h"

Heal::Heal(AnimationParams animParams)
	: Effect(_heal)
{}

void Heal::affect(vector<std::shared_ptr<Stat>> myStats, std::vector<Target> targets)
{
	for (auto& target : targets)
	{
		auto currHP = target._stats[_hp]->getStat();
		target._stats[_hp]->setStat(currHP + myStats[_dmg]->getStat());
	}
}
