#pragma once
#include "Effect.h"

class LifeDrain : public Effect
{
public:
	LifeDrain();

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) override;
};