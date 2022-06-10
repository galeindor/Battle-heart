#include "Effects/Heal.h"

#include "Characters/Character.h"

Heal::Heal(AnimationParams animParams)
	: Effect(_heal)
{}

void Heal::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, vector < shared_ptr<Character>> targets, float factor)
{
	for (auto& target : targets)
	{
		auto currHP = target->getStat(_hp);
		target->setStat(_hp,currHP + (baseValue + factor * myStats[_dmg]->getStat()));
	}
}
