#pragma once
#include "Effect.h"

class LifeDrain : public Effect
{
public:
	LifeDrain(AnimationParams animParams);

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) override;
};