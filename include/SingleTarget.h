#pragma once
#include "SkillDomain.h"

class SingleTarget : public SkillDomain
{
public:
	SingleTarget();
	~SingleTarget() = default;
private:
	std::shared_ptr<sf::Vector2f> m_target;
};

