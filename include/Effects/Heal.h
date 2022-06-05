#pragma once
#include "Effects/Effect.h"

class Heal : public Effect
{
public:
	Heal(AnimationParams animParams);
	~Heal() = default;

	virtual void affect(vector<std::shared_ptr<Stat>> myStats, 
						std::vector<Target> targets) override;
};