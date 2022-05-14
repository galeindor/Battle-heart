#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(const sf::Vector2f pos, int index);

	//overrides
	void draw(sf::RenderWindow& window) override;

	//-------------------
	void update(float deltaTime) override;

	//setters

	void setSelected(bool state) { this->m_selected = state; }
	//handling skills
	bool checkSkillClick(const sf::Vector2f& loc);
	//void handleSkill();

private:
	
	bool m_selected;
};