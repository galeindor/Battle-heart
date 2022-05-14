#pragma once

#include "Player.h"

class Knight : public Player
{
public:
	Knight(const sf::Vector2f pos);
	~Knight() = default;

	void handleCollision(GameObject& object) override;
	void handleCollision(Dummy& Dummy) override;
	void handleCollision(Cleric& cleric) override;
	void handleColiision(Knight& knight) override;
private:

};
