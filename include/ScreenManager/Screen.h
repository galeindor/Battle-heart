#pragma once
#include "Resources.h"
class Controller;

enum class ScreenState {
	MENU,
	PLAY,
	LEVEL_SELECT,
	HELP,
	SETTINGS,
	EXIT
};

class Screen
{
public:
	Screen(Controller* controller) : m_controller(controller) {}
	virtual ~Screen() = default;

	virtual void run(sf::RenderWindow& window);
	virtual void init() = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;


protected:
	virtual void initButtons() = 0;
	virtual void handleHover(const sf::Vector2f& hoverPos) = 0;
	virtual void handleMouseClick(const sf::Vector2f& hoverPos, sf::RenderWindow& window) = 0;
	void setBG(const int index);
	void drawBG(sf::RenderWindow& window) { window.draw(this->m_bg); }
	sf::RectangleShape m_bg;
	Controller* m_controller;
};

