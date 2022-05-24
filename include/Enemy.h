#pragma once
#include "GameObject.h"
#include "Knight.h"
#include "Cleric.h"

class Enemy : public GameObject
{
public:
	Enemy(sf::Vector2f enemy, const int index);
	void draw(sf::RenderWindow& window) override;

	virtual bool setTarget(Enemy& obj) override;
	virtual bool setTarget(Player& obj) override;
	virtual bool checkIntersection() const override;

private:
	virtual sf::Vector2f randEnemyPos() = 0;
	sf::Vector2f m_prevPosition;
};