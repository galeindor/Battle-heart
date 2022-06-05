#pragma once

#include "Player.h"

class Archer : public Player
{
public:
	Archer(const sf::Vector2f pos);
	~Archer() = default;

protected:
	virtual void initSkills(int index) override;

};
