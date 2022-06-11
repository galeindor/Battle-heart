#include "ScreenManager/Gameplay.h"

Gameplay::Gameplay(Controller* controller)
	: m_currLvl(0), m_board(Board(controller->getLevelInfo(0))),
	  Screen(controller)
{}

void Gameplay::update(const float deltaTime)
{
	if (!this->m_wonLevel && !this->m_paused && !this->m_lost)
	{
		auto state = this->m_board.updateBoard(deltaTime, this->m_charSelected);
		if (state == _winLevel)
		{
			if (!this->winLevel())
				this->winGame();
			else
				this->m_gameState.setTexture(*Resources::instance().getGameStateText(_winLevel));
		}
		else if (state == _loseLevel)
		{
			this->m_lost = true;
			this->m_gameState.setTexture(*Resources::instance().getGameStateText(_loseLevel));
		}
	}
}

void Gameplay::init()
{
	this->m_currLvl = this->m_controller->getCurrLvl();
	this->setBG(_firstLevel);
	this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl));
	this->initButtons();
}

void Gameplay::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	this->m_board.drawBoard(window, this->m_charSelected);
	window.draw(this->m_pauseButton);

	if (this->m_paused || this->m_wonLevel || this->m_lost)
	{
		window.draw(this->m_gameState);
		if(!this->m_lost)
			window.draw(this->m_continueButton);

		window.draw(this->m_restartButton);
		window.draw(this->m_exitButton);
	}
}

bool Gameplay::winLevel()
{
	this->m_currLvl++;
	this->m_controller->setMaxLvlAchieved(this->m_currLvl);
	this->m_controller->setCurrLvl(this->m_currLvl);
	if (this->m_controller->getGameWon(this->m_currLvl))
		return false;
	
	this->m_wonLevel = true;
	return true;
}

void Gameplay::winGame()
{
	this->m_wonGame = true;
	exit(EXIT_SUCCESS);
}

void Gameplay::initButtons()
{
	// Pause
	this->m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pause));
	this->m_pauseButton.setPosition(pauseButtonPos);

	// Continue
	this->m_continueButton.setTexture(*Resources::instance().getGameButtonText(_continue));
	this->m_continueButton.setPosition(continueButtonPos);

	// Restart
	this->m_restartButton.setTexture(*Resources::instance().getGameButtonText(_restart));
	this->m_restartButton.setPosition(restartButtonPos);

	// Exit
	this->m_exitButton.setTexture(*Resources::instance().getGameButtonText(_exitButton));
	this->m_exitButton.setPosition(exitButtonPos);
}

void Gameplay::handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window)
{
	// If not paused
	if (!this->m_paused)
	{
		if (this->m_pauseButton.getGlobalBounds().contains(hoverPos))
			this->m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pauseHL));
		else
			this->m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pause));
	}
	
	if(this->m_paused || this->m_wonLevel || this->m_lost)
	{
		// Continue
		if (!this->m_lost)
		{
			if (this->m_continueButton.getGlobalBounds().contains(hoverPos))
				this->m_continueButton.setTexture(*Resources::instance().getGameButtonText(_continueHL));
			else
				this->m_continueButton.setTexture(*Resources::instance().getGameButtonText(_continue));
		}

		// Restart
		if (this->m_restartButton.getGlobalBounds().contains(hoverPos))
			this->m_restartButton.setTexture(*Resources::instance().getGameButtonText(_restartHL));
		else
			this->m_restartButton.setTexture(*Resources::instance().getGameButtonText(_restart));

		// Exit
		if (this->m_exitButton.getGlobalBounds().contains(hoverPos))
			this->m_exitButton.setTexture(*Resources::instance().getGameButtonText(_exitButtonHL));
		else
			this->m_exitButton.setTexture(*Resources::instance().getGameButtonText(_exitButton));
	}
}

void Gameplay::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (this->m_paused || this->m_wonLevel || this->m_lost)
	{
		if (!this->m_lost && this->m_continueButton.getGlobalBounds().contains(clickPos))
		{
			if (this->m_wonLevel)
			{
				this->m_wonLevel = false;
				this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl));
			}
			else
				this->m_paused = false;
		}
		else if (this->m_restartButton.getGlobalBounds().contains(clickPos))
		{
			if(this->m_wonLevel)
				this->m_board = Board(this->m_controller->getLevelInfo(--this->m_currLvl));
			else
				this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl));

			this->m_wonLevel = false;
			this->m_lost = false;
			this->m_paused = false;
		}
		else if (this->m_exitButton.getGlobalBounds().contains(clickPos))
		{
			this->m_lost = false;
			this->m_wonLevel = false;
			this->m_paused = false;
			this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl));
			this->m_controller->setCurrentScreen(ScreenState::MENU);
		}
	}
	else
	{
		if (!this->m_charSelected)
			this->m_charSelected = this->m_board.handleFirstClick(clickPos);

		else // if a click made the player move - charSelected is no longer true
			this->m_charSelected = !m_board.handleSecondClick(clickPos);
	}

	if (this->m_pauseButton.getGlobalBounds().contains(clickPos))
	{
		this->m_gameState.setTexture(*Resources::instance().getGameStateText(_pauseLevel));
		this->m_paused = true;
	}
}
