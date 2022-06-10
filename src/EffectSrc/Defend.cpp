#include "Effects/Defend.h"

#include "Characters/Character.h"

Defend::Defend(AnimationParams animParams)
	: Effect(_defend)
{}

void Defend::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, vector <shared_ptr<Character>> targets, float factor)
{
	for (auto& target : targets)
	{
		auto currDef = target->getStat(_defence);
		target->setStat(_defence , currDef * factor);
	}
}
