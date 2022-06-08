#include "Effects/Heal.h"

#include "Characters/Character.h"

Heal::Heal(AnimationParams animParams)
	: Effect(_heal)
{}

void Heal::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, std::vector<Character*> targets)
{
	for (auto& target : targets)
	{
		auto currHP = target->getStat(_hp);
		target->setStat(_hp,currHP + (baseValue + myStats[_dmg]->getStat()));
	}
}
