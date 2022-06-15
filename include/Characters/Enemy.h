#pragma once
#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
public:
	Enemy(const int index);

	// Virtuals
	virtual void draw(sf::RenderWindow& window) override;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) override;
	virtual bool setTarget(std::shared_ptr<Player> obj) override;
	virtual bool checkIntersection() const override;

	// Returns a new shared ptr for a specific enemy character 

protected:
	virtual shared_ptr<Enemy> getType() = 0;

private:

	sf::Vector2f randEnemyPos();
};