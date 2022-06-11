
#include "Controller.h"
int Controller::currentScreen = 0;

Controller::Controller()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battle Heart"),
	  m_levelLoader(LevelLoader(LevelsFileName)),
	  m_currLvl(0), m_board(Board(m_levelLoader.getLevel(0)))
{
	this->m_bg.setTexture(*Resources::instance().getBackground(_firstLevel));
	this->m_bg.setColor(sf::Color(255, 255, 255, 255));
}

//=======================================================================================

void Controller::run()
{
	this->m_menu.runMenu(this->m_window);
	float deltaTime = 0.f;

	while (m_window.isOpen())
	{
		drawGame();
		deltaTime = this->m_clock.restart().asSeconds();
		this->update(deltaTime);
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

				if (event.mouseButton.button == sf::Mouse::Button::Left)
					handleMouseClick(location);
				break;
			}

		}
	}
}

//=======================================================================================

void Controller::update(float deltaTime)
{
	if (this->m_board.updateBoard(deltaTime, this->m_charSelected))
		if (!this->winLevel())
			this->winGame();
}

//=======================================================================================

bool Controller::winLevel()
{
	this->m_currLvl++;
	if (this->m_levelLoader.getGameEnded(this->m_currLvl))
		return false;
	
	this->m_board = Board(this->m_levelLoader.getLevel(this->m_currLvl));
}

//=======================================================================================

void Controller::winGame()
{
	exit(EXIT_SUCCESS);
}

//=======================================================================================

void Controller::handleMouseClick(sf::Vector2f location)
{
	if (!this->m_charSelected)
		this->m_charSelected = this->m_board.handleFirstClick(location);

	else // if a click made the player move - charSelected is no longer true
		this->m_charSelected = !m_board.handleSecondClick(location);
}


//=======================================================================================

void Controller::drawGame()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_bg);

	this->m_board.drawBoard(this->m_window, this->m_charSelected);

	m_window.display();
}