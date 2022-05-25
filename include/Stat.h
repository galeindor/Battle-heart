#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

class Stat
{
public:
	Stat(int initVal);
	~Stat() = default;

	virtual bool handleStat(int amount);

	int getStat() { return this->m_val; }
	int setStat(int val);

protected:


private:
	int m_val;
};