#include "Stat.h"

Stat::Stat(float initVal) // init stat value
	: m_val(initVal)
{}

bool Stat::handleStat(float amount) //lower stat and check for higher the 0.f
{
	m_val -= amount;
	return (m_val > 0.f);
}
