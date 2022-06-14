#pragma once
#include "Effects/Effect.h"

class Damage : public Effect
{
public:
	Damage();

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
						Character* target, float factor) override;
};