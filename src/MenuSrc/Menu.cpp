#include "Menu/Menu.h"

Menu::Menu()
{
	this->initBG();
	this->initButtons();
}

void Menu::runMenu(sf::RenderWindow& window)
{
	this->m_running = true;

	while (window.isOpen() && this->m_running)
	{
		this->render(window);
		this->pollEvents(window);
	}
}

void Menu::drawMenu(sf::RenderWindow& window)
{
	window.draw(m_bg);
	this->drawButtons(window);
}

void Menu::drawButtons(sf::RenderWindow& window)
{
	for (auto& button : this->m_buttons)
		window.draw(button);
}

void Menu::pollEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed: // Closed game.
			exit(EXIT_SUCCESS);
			break;

		case sf::Event::KeyPressed: // Pressed a key in the keyboard.
			if (event.key.code == sf::Keyboard::Escape) // Exit.
				exit(EXIT_SUCCESS);
			break;

		case sf::Event::MouseButtonReleased: // Clicked on the menu.
			this->handleClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
			break;

		case sf::Event::MouseMoved: // Moved the mouse on the menu.
		{
			auto mouse_loc = sf::Vector2f(sf::Mouse::getPosition(window)); // Current position of the mouse.
			this->hoverButtons(mouse_loc);
			break;
		}

		default:
			break;
		}
	}
}

void Menu::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);
	this->drawMenu(window);
	window.display();
}

void Menu::handleClick(sf::Vector2f pos)
{
	for (int index = 0; index < this->m_buttons.size(); index++)
		if (this->m_buttons[index].getGlobalBounds().contains(pos))
		{
			switch (index)
			{
			case MenuButtons::_battle:
				this->m_running = false;
				break;
			case MenuButtons::_levels:
				break;
			case MenuButtons::_escape:
				exit(EXIT_SUCCESS);
			}
		}
			
}

void Menu::hoverButtons(sf::Vector2f pos)
{
	for (int index = 0; index < this->m_buttons.size(); index++)
	{
		if (this->m_buttons[index].getGlobalBounds().contains(pos))
		{
			this->m_buttons[index].setOutlineColor(sf::Color::Black);
			this->m_buttons[index].setOutlineThickness(5);
		}
		else
			this->m_buttons[index].setOutlineThickness(0);
	}
}

void Menu::initBG()
{
	this->m_bg.setTexture(*Resources::instance().getBackground(_menu));
	this->m_bg.setColor(sf::Color(255, 255, 255, 255));
}

void Menu::initButtons()
{
	sf::Text tempText;
	tempText.setFont(*Resources::instance().getButtonsFont());
	tempText.setStyle(sf::Text::Style::Bold);
	tempText.setCharacterSize(70);

	for (int i = 0; i < NUM_OF_MBUTTONS; i++)
	{
		tempText.setString(MENU_BUTTONS_STRINGS[i]);

		if(i == _battle)
			tempText.setPosition(sf::Vector2f(MENU_BUTTONS_START.x, MENU_BUTTONS_START.y));
		else if (i == _levels)
			tempText.setPosition(sf::Vector2f(MENU_BUTTONS_START.x - 2 * MENU_BUTTONS_GAP, 
											  MENU_BUTTONS_START.y + (MENU_BUTTONS_OFFSET + 1.5 * MENU_BUTTONS_GAP) * i));
		else
			tempText.setPosition(sf::Vector2f(MENU_BUTTONS_START.x - 2 * MENU_BUTTONS_GAP, 
											  MENU_BUTTONS_START.y + MENU_BUTTONS_OFFSET * i));

		this->m_buttons.push_back(tempText);
	}
}
