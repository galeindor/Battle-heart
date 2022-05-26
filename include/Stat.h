#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

class Stat
{
public:
	Stat(int initVal);
	~Stat() = default;

	virtual bool handleStat(int amount);

	int getStat() const { return this->m_val; }
	void setStat(int val) { this->m_val = val; }

protected:


private:
	int m_val;
};