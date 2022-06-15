#pragma once
#include "Effect.h"

class Defend : public Effect
{
public:
	Defend();

	virtual void affect(vector<std::shared_ptr<Stat>> myStats,
		Character* target, float factor) override;
};