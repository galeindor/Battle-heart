#pragma once
#include "Effect.h"

class Defend : public Effect
{
public:
	Defend(AnimationParams animParams);
	~Defend() = default;

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
		std::vector<Target> targets) override;
};