#pragma once

#include "Player.h"

class Knight : public Player
{
public:
	Knight(const sf::Vector2f pos);

	virtual shared_ptr<Player> getType() {
		return make_shared<Knight>(startPositions[_knight]);
	}

	virtual void initSkills(const int index) override;
protected:

};
