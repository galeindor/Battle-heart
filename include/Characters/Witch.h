#pragma once

#include "Player.h"

class Witch : public Player
{
public:
	Witch(const sf::Vector2f pos);
	~Witch() = default;
	virtual shared_ptr<Player> getType() {
		return make_shared<Witch>(startPositions[_witch]);
	}

	virtual void initSkills(const int index) override;
};
