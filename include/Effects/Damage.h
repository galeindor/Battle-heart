#pragma once
#include "Effects/Effect.h"

class Damage : public Effect
{
public:
	Damage(AnimationParams animParams);

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
					vector<Character*> targets) override;
};