#pragma once

#include "Resources.h"
#include "Player.h"

class Cleric : public Player
{
public:
	Cleric(const sf::Vector2f pos);
	~Cleric() = default;

	void hitPlayer();

private:

};