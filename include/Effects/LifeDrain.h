#pragma once
#include "Effect.h"

class LifeDrain : public Effect
{
public:
	LifeDrain();

	virtual void affect(vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) override;
};