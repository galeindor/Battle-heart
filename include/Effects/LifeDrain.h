#pragma once
#include "Effect.h"

class LifeDrain : public Effect
{
public:
	LifeDrain(AnimationParams animParams);

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
		vector<shared_ptr<Character>> targets, float factor) override;
};