#include "Effects/DmgByDistance.h"

#include "Characters/Character.h"

DmgByDistance::DmgByDistance()
{}

void DmgByDistance::affect(vector<std::shared_ptr<Stat>> myStats, Character* target, float factor)
{
	auto currHP = target->getStat(_hp);
	auto dmgByDefence = (myStats[_dmg]->getStat() * factor / target->getStat(_defence));

	auto distance = sqrt(pow(myPos.x - tarPos.x, 2) + pow(myPos.y - tarPos.y, 2));
	target->setStat(_hp, currHP - dmgByDefence);
}
