#include "Effects/Damage.h"

Damage::Damage(AnimationParams animParams)
	: Effect(_damage)
{}

void Damage::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, std::vector<Target> targets)
{
	for (auto& target : targets)
	{
		auto currHP = target._stats[_hp]->getStat();
		auto dmgByDefence = (myStats[_dmg]->getStat() + baseValue) * (myStats[_defend]->getStat() / 100);
		target._stats[_hp]->setStat(currHP - dmgByDefence);
	}
}
