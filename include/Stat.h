#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

class Stat
{
public:
	Stat(float initVal);
	~Stat() = default;


	int getStat() const { return this->m_val; }
	void setStat(float val) { this->m_val = val; }

protected:
	virtual bool handleStat(float amount);


private:
	float m_val;
};