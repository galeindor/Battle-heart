#pragma once

#include "Resources.h"
#include "Player.h"

class Cleric : public Player
{
public:
	Cleric(const sf::Vector2f pos);
	~Cleric() = default;

	virtual bool setTarget(Player& obj) override;
	virtual bool setTarget(Enemy& obj) override;

	void handleCollision(GameObject& object) override;
	void handleCollision(Dummy& dummy) override;
	void handleCollision(Cleric& cleric) override;
	void handleColiision(Knight& knight) override;

private:

};