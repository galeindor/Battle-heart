#pragma once
#include "Screen.h"
#include "Board.h"
#include "Controller.h"

class Gameplay : public Screen
{
public:
	Gameplay(Controller* controller);
	virtual ~Gameplay() = default;

	//
	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

	//
	bool winLevel();
	void winGame();

protected:
	virtual void handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	Controller* m_controller;
	Board m_board;
	bool m_charSelected = false;
	unsigned int m_currLvl;
};