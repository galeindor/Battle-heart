#pragma once
#include "Effects/Effect.h"

// This class is in charge of the damage effect.
// It inflicts damage to characters.
class Damage : public Effect
{
public:
	Damage();
	virtual void affect(vector<std::shared_ptr<Stat>> myStats,
						Character* target, float factor) override;
};