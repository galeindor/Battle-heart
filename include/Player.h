#pragma once

#include "GameObject.h"
#include "Enemy.h"

class Player : public GameObject
{
public:
	Player(const sf::Vector2f pos, int index);

	// Virtuals
	virtual void draw(sf::RenderWindow& window) override;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) override;
	virtual bool setTarget(std::shared_ptr<Player> obj) override;
	virtual bool checkIntersection() const override;


	void setSelected(bool state) { this->m_selected = state; }
	bool checkSkillClick(const sf::Vector2f& loc);

private:
	bool m_selected;
};