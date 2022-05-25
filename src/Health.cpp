
#include "Health.h"

Health::Health(int initVal)
	: Stat(initVal)
{}

bool Health::handleStat(int amount)
{
	this->getStat() -= amount;
	return (this->getStat() > 0);
}


