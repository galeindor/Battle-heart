#include "Effects/Defend.h"

Defend::Defend(AnimationParams animParams)
	: Effect(_defend)
{}

void Defend::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, std::vector<Target> targets)
{
	for (auto& target : targets)
	{
		auto currDef = target._stats[_defend]->getStat();
		target._stats[_defend]->setStat(currDef * 1.2f);
	}
}
