#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"
#include "Stat.h"

class Health : public Stat
{
public:
	Health(int initVal);
	virtual bool handleStat(int amount) override;
};
