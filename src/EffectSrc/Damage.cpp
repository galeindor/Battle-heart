#include "Effects/Damage.h"

#include "Characters/Character.h"

Damage::Damage(AnimationParams animParams)
	: Effect(_damage)
{}

void Damage::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, vector <shared_ptr<Character>> targets , float factor)
{
	for (auto& target : targets)
	{
		auto currHP = target->getStat(_hp);
		auto dmgByDefence = (myStats[_dmg]->getStat() + baseValue) * ((float(myStats[_defend]->getStat())* factor / 100));
		target->setStat(_hp,currHP - dmgByDefence);
	}
}
