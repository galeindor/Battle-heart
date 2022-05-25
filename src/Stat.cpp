#include "Stat.h"

Stat::Stat(int initVal)
	: m_val(initVal)
{}

bool Stat::handleStat(int amount)
{
	m_val -= amount;
	return (m_val > 0);
}
