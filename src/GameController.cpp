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
	auto inProgress = false;
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
					if (!inProgress)
					{
						inProgress = true;
						MouseClick(location);	
					}
					break;
				}
				break;
			}
		}
		inProgress = false;
		
	}
}

//=======================================================================================

void GameController::MouseClick(sf::Vector2f location)
{

	static bool stopCondition = false;

	for (int i= 0; i < m_players.size(); i++)
	{
		if (m_players[i]->checkCollision(location))
		{
			m_selected.setPosition(m_players[i]->getPosition().x, m_players[i]->getPosition().y);
			m_charSelected = true;

			while (!stopCondition)
			{
				m_selected.setColor(sf::Color::White);
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

						if (outOfRange(mouseLoc))
							break;

						m_selected.setPosition(mouseLoc);

						auto found = false;
						if (!stopCondition)
						{
							stopCondition = true;
							for (int j = 0; j < m_players.size(); j++)
							{
								if (m_players[j]->checkCollision(mouseLoc) && i == _cleric)
								{
									m_selected.setPosition(m_players[j]->getPosition());
									m_selected.setColor(sf::Color::Magenta);
									drawGame();
									found = true;
									break;
								}
							}
							if(!found)
								updatePlayer( i , mouseLoc );
						}
						break;
					}
				}
				m_charSelected = false;
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

void GameController::updatePlayer(int playerIndex , sf::Vector2f dest)
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

//=======================================================================================

bool GameController::outOfRange(sf::Vector2f location)
{
	return (location.x >= WINDOW_WIDTH - CUT_CORNERS || location.x <= CUT_CORNERS ||
			location.y >= WINDOW_HEIGHT - CUT_CORNERS || location.y <= HEIGHT_LIMIT);
}

//=======================================================================================

//=======================================================================================

//=======================================================================================

//=======================================================================================
