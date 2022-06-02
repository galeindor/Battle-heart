
#pragma once

#include "Skill.h"

class ClericSkill : public Skill
{
public:
	ClericSkill(sf::Texture* texture, const sf::Vector2f& pos, float cooldown, int damage, float range, int wantedStat);

	virtual int castSkill(Stat stat) = 0 ;

private:

};
