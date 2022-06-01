#pragma once
#include "SkillDomain.h"

class SingleTarget : public SkillDomain
{
public:
private:
	std::shared_ptr<sf::Vector2f> m_target;
};

