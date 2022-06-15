#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

// This class is in charge of stats in the game.
// Stats represent different variables in the game-
// Such as health, speed, defense, etc. 
class Stat
{
public:
	// C-tor and d-tor.
	Stat(float initVal);
	~Stat() = default;

	// Management.
	float getStat() const { return this->m_val; }
	void setStat(float val) { this->m_val = val; }

private:
	bool handleStat(float amount);
	float m_val; // value of the stat
};