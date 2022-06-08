#include "Effects/Damage.h"

#include "Characters/Character.h"

Damage::Damage(AnimationParams animParams)
	: Effect(_damage)
{}

void Damage::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, vector < Character*> targets)
{
	for (auto& target : targets)
	{
		auto currHP = target->getStat(_hp);
		auto dmgByDefence = (myStats[_dmg]->getStat() + baseValue) * (myStats[_defend]->getStat() / 100);
		target->setStat(_hp,currHP - dmgByDefence);
	}
}
