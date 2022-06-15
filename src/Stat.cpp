#include "Stat.h"

Stat::Stat(float initVal)
	: m_val(initVal)
{}

bool Stat::handleStat(float amount)
{
	m_val -= amount;
	return (m_val > 0.f);
}
