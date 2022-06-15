#pragma once
#pragma once

#include "Player.h"

class Archer : public Player
{
public:
	Archer(const sf::Vector2f pos);

	virtual shared_ptr<Player> getType() {
		return make_shared<Archer>(startPositions[_archer]);
	}

	virtual void initSkills(const int index) override;
protected:

};
