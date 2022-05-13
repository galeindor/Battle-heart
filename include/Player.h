#pragma once

#include "GameObject.h"


class Player : public GameObject
{
public:
	Player(const sf::Vector2f pos, int index);

	void draw(sf::RenderWindow& window) override;
	bool moveValidator();
	void updatePlayer(float deltaTime);
	void move(float deltaTime) override;
	void setDestination(sf::Vector2f dest) { this->m_dest = dest; }
	bool getIsMoving() const { return this->m_isMoving; }
	void setSelected(bool state) { this->m_selected = state; }

private:

	bool m_isMoving;
	bool m_selected;
	sf::Vector2f m_dest;

};