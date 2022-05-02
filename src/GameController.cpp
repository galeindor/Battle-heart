
#include "GameController.h"

GameController::GameController()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BattleHeart") , m_cleric(sf::Vector2f(200,200))
{
	m_bg.setTexture(*Resources::instance().getBackground(0));
	m_bg.setColor(sf::Color(255, 255, 255, 255));
	m_selected.setTexture(*Resources::instance().getTexture(_select));

	auto origin = m_selected.getOrigin();
	m_selected.setOrigin( origin.x + 45 , origin.y - 20);

}

//=======================================================================================

void GameController::run()
{
	while (m_window.isOpen())
	{
		drawGame();

		for (auto event = sf::Event{}; m_window.pollEvent(event); )
		{
 			switch (event.type)
			{

			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonPressed:
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					MouseClick(location);
					break;
				}
				break;
			}
		}
		
	}
}

//=======================================================================================

void GameController::MouseClick(sf::Vector2f location)
{

	static bool stopCondition = false;
	if (m_cleric.handleCollision(location))
	{
		m_selected.setPosition(m_cleric.getPosition().x , m_cleric.getPosition().y);
		m_charSelected = true;

		while (!stopCondition)
		{

			drawGame();

			for (auto event = sf::Event{}; m_window.waitEvent(event) && !stopCondition; )
			{
				switch (event.type)
				{

				case sf::Event::Closed:
					m_window.close();
					break;

				case sf::Event::MouseButtonPressed:

					auto mouseLoc = m_window.mapPixelToCoords(
						{ event.mouseButton.x, event.mouseButton.y });

					m_selected.setPosition(mouseLoc);

					if (!stopCondition)
					{
						stopCondition = true;
						movePlayer(mouseLoc);
						m_charSelected = false;
					}
					break;
				}
			}
		}
	}
	stopCondition = false;
}


//=======================================================================================

void GameController::drawGame()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_bg);

	if(m_charSelected)
		m_window.draw(m_selected);

	m_cleric.draw(m_window);
	m_window.display();
}

//=======================================================================================

void GameController::movePlayer(sf::Vector2f dest)
{
	sf::Clock clock;

	auto direction = dest - m_cleric.getPosition();

	while (m_cleric.moveValidator(dest))
	{
		auto delta = clock.restart().asSeconds();
		m_cleric.movePlayer(direction, delta);
		drawGame();
	}
}