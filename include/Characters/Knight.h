#pragma once

#include "Player.h"

class Knight : public Player
{
public:
	Knight(const sf::Vector2f pos);
	~Knight() = default;
protected:
	virtual void initSkills(const int index) override;

};
