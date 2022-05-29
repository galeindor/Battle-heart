#pragma once
#include "macros.h"
#include "Resources.h"

class Menu
{
public:
	Menu();
	~Menu() = default;

	void runMenu(sf::RenderWindow& window);
	void drawMenu(sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);
	void pollEvents(sf::RenderWindow& window); // New events handler.
	void render(sf::RenderWindow& window); // Function to display the menu.
	void handleClick(sf::Vector2f pos);
	void hoverButtons(sf::Vector2f pos);
private:
	void initBG();
	void initButtons();

	bool m_running;
	sf::Sprite m_bg;
	std::vector<sf::Text> m_buttons;
};