#pragma once
#include "Domain.h"

class Single : public Domain
{
public:
	Single();
	~Single() = default;
private:
	sf::Vector2f m_target;
};

