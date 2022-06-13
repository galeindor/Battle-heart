#include "Stat.h"

Stat::Stat(float initVal)
	: m_val(initVal)
{}

bool Stat::handleStat(float amount)
{
	m_val -= amount;
	m_val = std::max(0.f, m_val);
	return (m_val > 0.f);
}
