#pragma once

#include "macros.h"

class Impact
{
public:
	Impact();
	~Impact();

	bool reachedTarget();

	void update();

private:
	unsigned int m_splitNumber;
};