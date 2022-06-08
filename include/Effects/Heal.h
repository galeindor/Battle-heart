#pragma once
#include "Effects/Effect.h"

class Heal : public Effect
{
public:
	Heal(AnimationParams animParams);

	virtual void affect(float baseValue , vector<std::shared_ptr<Stat>> myStats, 
						vector<shared_ptr<Character>> targets) override;
};