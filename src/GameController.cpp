
#include "GameController.h"

GameController::GameController()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battle Heart")
{
	m_bg.setTexture(*Resources::instance().getBackground(0));
	m_bg.setColor(sf::Color(255, 255, 255, 255));
	m_selected.setTexture(*Resources::instance().getTexture(_select));

	m_players.push_back(std::make_unique < Cleric >(sf::Vector2f(200, 200)));
	m_players.push_back(std::make_unique < Knight >(sf::Vector2f(300, 300)));

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
	for (int i= 0; i< m_players.size(); i++)
	{

		if (m_players[i]->checkCollision(location))
		{
			m_selected.setPosition(m_players[i]->getPosition().x, m_players[i]->getPosition().y);
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
							movePlayer( i , mouseLoc );
							m_charSelected = false;
						}
						break;
					}
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

	for (int i = 0; i < m_players.size(); i++)
	{
		m_players[i]->draw(m_window);
	}
	m_window.display();
}

//=======================================================================================

void GameController::movePlayer(int playerIndex , sf::Vector2f dest)
{
	sf::Clock clock;

	auto direction = dest - m_players[playerIndex]->getPosition();

	while (m_players[playerIndex]->moveValidator(dest))
	{
		auto delta = clock.restart().asSeconds();
		m_players[playerIndex]->movePlayer(direction, delta);
		drawGame();
	}
}