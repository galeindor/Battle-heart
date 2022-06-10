#include "Effects/Defend.h"

#include "Characters/Character.h"

Defend::Defend(AnimationParams animParams)
	: Effect(_defend)
{}

void Defend::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, Character* target, float factor)
{
	auto currDef = target->getStat(_defence);
	target->setStat(_defence, currDef * factor);
}
