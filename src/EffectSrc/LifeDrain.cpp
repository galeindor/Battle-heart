#include "Effects/LifeDrain.h"

#include "Characters/Character.h"

LifeDrain::LifeDrain()
{}

void LifeDrain::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, Character* target, float factor)
{
	auto currHP = target->getStat(_hp);
	auto dmgByDefence = (myStats[_dmg]->getStat() * factor / target->getStat(_defence)) ;
	target->setStat(_hp, currHP - dmgByDefence);
	myStats[_hp]->setStat(myStats[_hp]->getStat() + dmgByDefence * 0.5);
}
