#include "ScreenManager/Menu.h"

void Menu::update(const float deltaTime)
{
}

void Menu::init()
{
	this->setBG(_menu);
	this->initButtons();
}

void Menu::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	for (auto& button : this->m_buttons)
		window.draw(button);
}

void Menu::initButtons()
{
	sf::Text tempText;
	tempText.setFont(*Resources::instance().getFont());
	tempText.setStyle(sf::Text::Style::Bold);
	tempText.setCharacterSize(70);

	for (int i = 0; i < NUM_OF_MBUTTONS; i++)
	{
		tempText.setString(MENU_BUTTONS_STRINGS[i]);

		if (i == _battle)
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

void Menu::handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window)
{
	for (int index = 0; index < this->m_buttons.size(); index++)
	{
		if (this->m_buttons[index].getGlobalBounds().contains(hoverPos))
		{
			this->m_buttons[index].setOutlineColor(sf::Color::Black);
			this->m_buttons[index].setOutlineThickness(4);
		}
		else
			this->m_buttons[index].setOutlineThickness(0);
	}
}

void Menu::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	auto sound = Resources::instance().sound();

	for (int index = 0; index < this->m_buttons.size(); index++)
		if (this->m_buttons[index].getGlobalBounds().contains(clickPos))
		{
			switch (index)
			{
				// Clicking on battle results in continuing from last point.
			case MenuButtons::_battle:
				sound->playSound(int(Sound::Sounds::BATTLE));
				this->m_controller->setCurrentScreen(ScreenState::PLAY);
				break;
				// Clicking on levels results in picking a level.
			case MenuButtons::_levels:
				this->m_controller->setCurrentScreen(ScreenState::LEVEL_SELECT);
				break;
			case MenuButtons::_escape:
				this->m_controller->setCurrentScreen(ScreenState::EXIT);
				break;
			}
		}
}
