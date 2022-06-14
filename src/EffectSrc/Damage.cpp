#include "Effects/Damage.h"

#include "Characters/Character.h"

Damage::Damage()
{}

void Damage::affect(float baseValue, vector<std::shared_ptr<Stat>> myStats, Character* target , float factor)
{
	auto currHP = target->getStat(_hp);
	auto dmgByDefence = ( myStats[_dmg]->getStat() * factor / target->getStat(_defence) ) ;
	target->setStat(_hp, currHP - dmgByDefence);
}
