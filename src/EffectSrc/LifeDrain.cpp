#include "Effects/LifeDrain.h"

#include "Characters/Character.h"

LifeDrain::LifeDrain(AnimationParams animParams)
	: Effect(_drainLife)
{}

void LifeDrain::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, vector < shared_ptr<Character>> targets, float factor)
{
	for (auto& target : targets)
	{
		auto currHP = target->getStat(_hp);
		auto dmgByDefence = (myStats[_dmg]->getStat() + baseValue) * ((float(myStats[_dmg]->getStat())*factor / 100));
		target->setStat(_hp, currHP - dmgByDefence);
		myStats[_hp]->setStat( myStats[_hp]->getStat() + dmgByDefence * 0.5);
	}
}
