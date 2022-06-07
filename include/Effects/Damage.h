#pragma once
#include "Effects/Effect.h"

class Damage : public Effect
{
public:
	Damage(AnimationParams animParams);
	~Damage() = default;

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
						std::vector<Target> targets) override;
};