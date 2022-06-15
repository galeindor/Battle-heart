#pragma once
#include "Effect.h"

// This class is in charge of the defend effect.
class Defend : public Effect
{
public:
	Defend();

	virtual void affect(vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) override;
};