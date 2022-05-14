#pragma once

#include "Resources.h"
#include "Player.h"

class Cleric : public Player
{
public:
	Cleric(const sf::Vector2f pos);
	~Cleric() = default;
	void handleCollision(GameObject& object) override;
	void handleCollision(Dummy& dummy) override;
	void handleCollision(Cleric& cleric) override;
	void handleColiision(Knight& knight) override;
	void hitPlayer();

private:

};