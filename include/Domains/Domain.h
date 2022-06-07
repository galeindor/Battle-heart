#pragma once
#include "macros.h"
#include "Stat.h"

class Character;
class Domain
{
public:
	Domain(std::vector<Target> targets);
	~Domain() = default;
	void setTargets(std::vector<Target> targets) { this->m_targets = targets; }
	std::vector<Target>& getTargets() { return this->m_targets; }
private:
	std::vector<Target> m_targets;
};