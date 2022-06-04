#pragma once
#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
public:
	Enemy(sf::Vector2f pos, const int index);

	// Virtuals
	virtual void draw(sf::RenderWindow& window) override;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) override;
	virtual bool setTarget(std::shared_ptr<Player> obj) override;
	virtual bool checkIntersection() const override;

private:
	virtual sf::Vector2f randEnemyPos() = 0;
};