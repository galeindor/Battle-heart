#pragma once

#include "Player.h"

class Knight : public Player
{
public:
	Knight(const sf::Vector2f pos);
	~Knight() = default;
	virtual shared_ptr<Player> getType() {
		return make_shared<Knight>(startPositions[_knight]);
	}
protected:

};
