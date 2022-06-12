#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

class Stat
{
public:
	Stat(float initVal);
	~Stat() = default;

	virtual bool handleStat(float amount);

	int getStat() const { return this->m_val; }
	void setStat(float val) { this->m_val = val; }

protected:


private:
	float m_val;
};