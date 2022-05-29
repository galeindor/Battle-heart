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

	//handling skills
	bool checkSkillClick(const sf::Vector2f& loc);

	//void handleSkill();

protected:
	virtual void initSkills(int index) = 0;

private:
	bool m_selected;

};