#pragma once

#include "Effects/Effect.h"

class Fear: public Effect
{
public:
	Fear();

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) override;
};

