#pragma once

#include "Resources.h"
#include "Player.h"

class Cleric : public Player
{
public:
	Cleric(const sf::Vector2f pos);
	~Cleric() = default;

	virtual bool setTarget(std::shared_ptr<Player> obj) override;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) override;

};