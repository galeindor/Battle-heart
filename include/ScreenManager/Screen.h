#pragma once
#include "Resources.h"

enum class ScreenState {
	MENU,
	PLAY,
	EXIT,
	LEVEL_SELECT
};

class Screen
{
public:
	Screen() = default;
	virtual ~Screen() = default;

	virtual void run(sf::RenderWindow& window);
	virtual void init() = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;


protected:
	virtual void handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window) = 0;
	virtual void handleMouseClick(const sf::Vector2f& hoverPos, sf::RenderWindow& window) = 0;
	void setBG(const int index);
	void drawBG(sf::RenderWindow& window) { window.draw(this->m_bg); }
	sf::RectangleShape m_bg;
};

