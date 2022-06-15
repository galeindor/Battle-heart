#pragma once

#include "Effects/Effect.h"

class Heal : public Effect
{
public:
	Heal();

	virtual void affect(vector<std::shared_ptr<Stat>> myStats, 
		Character* target, float factor) override;
};