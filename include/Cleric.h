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

protected:
	virtual void initSkills(int index) override;


};