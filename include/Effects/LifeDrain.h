#pragma once
#include "Effect.h"

// This class is in charge of the life drain effect.
class LifeDrain : public Effect
{
public:
	LifeDrain();
	virtual void affect(vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) override;
};