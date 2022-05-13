#pragma once

#include "Resources.h"
#include "HealthBar.h"
#include "Skill.h"

class Player
{
public:
	Player(const sf::Vector2f loc, int index);

	sf::Vector2f getPosition() const;
	void draw(sf::RenderWindow& window);
	bool checkCollision(sf::Vector2f loc);
	bool moveValidator();

	void updatePlayer(float deltaTime);
	void movePlayer(float deltaTime);
	void setDestination(sf::Vector2f dest) { this->m_dest = dest; }
	bool getIsMoving() const { return this->m_isMoving; }
	void setSelected(bool state) { this->m_selected = state; }

protected:

	bool m_isMoving;
	bool m_selected;
	sf::Vector2f m_dest;
	sf::Sprite m_sprite;
	HealthBar m_hpBar;

	vector < std::unique_ptr <Skill> > m_skills; // vector of skills
};