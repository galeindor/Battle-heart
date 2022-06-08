#include "Effects/Defend.h"

#include "Characters/Character.h"

Defend::Defend(AnimationParams animParams)
	: Effect(_defend)
{}

void Defend::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, std::vector<Character*> targets)
{
	for (auto& target : targets)
	{
		auto currDef = target->getStat(_defence);
		target->setStat(_defence , currDef * 1.2f);
	}
}
