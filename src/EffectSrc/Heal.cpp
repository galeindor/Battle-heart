#include "Effects/Heal.h"

#include "Characters/Character.h"

Heal::Heal()
{}

void Heal::affect(vector<std::shared_ptr<Stat>> myStats, Character* target, float factor)
{
	auto currHP = target->getStat(_hp);
	target->setStat(_hp,currHP + (factor * myStats[_dmg]->getStat()));
}
