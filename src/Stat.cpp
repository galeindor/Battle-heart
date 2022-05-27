#include "Stat.h"

Stat::Stat(int initVal)
	: m_val(initVal) , m_max(initVal)
{}

bool Stat::handleStat(int amount)
{
	m_val -= amount;
	m_val = std::max(0, m_val);
	//m_val = std::min(m_max, m_val);
	return (m_val > 0);
}
