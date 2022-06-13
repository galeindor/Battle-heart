#include "ScreenManager/Gameplay.h"

//-------------------------------------------------
Gameplay::Gameplay(Controller* controller)
	: m_currLvl(0), m_board(Board(controller->getLevelInfo(0))),
	Screen(controller)
{}
//-------------------------------------------------
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
		if (!this->m_lost)
			window.draw(this->m_buttons[_continueIndex]);

		window.draw(this->m_buttons[_restartIndex]);
		window.draw(this->m_buttons[_exitIndex]);
	}
}
//-------------------------------------------------
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
//-------------------------------------------------

void Gameplay::winGame()
{
	this->m_wonGame = true;
	exit(EXIT_SUCCESS);
}
//-------------------------------------------------

void Gameplay::initButtons()
{
	// Pause
	this->m_pauseButton.setTexture(*Resources::instance().getGameButtonText(_pause));
	this->m_pauseButton.setPosition(pauseButtonPos);

	// (Initialize the vector)
	sf::Sprite tempSprite;
	tempSprite.setTexture(*Resources::instance().getGameButtonText(_continue));
	tempSprite.setPosition(continueButtonPos);
	this->m_buttons.push_back(tempSprite);

	// Restart
	tempSprite.setTexture(*Resources::instance().getGameButtonText(_restart));
	tempSprite.setPosition(restartButtonPos);
	this->m_buttons.push_back(tempSprite);

	// Exit
	tempSprite.setTexture(*Resources::instance().getGameButtonText(_exitButton));
	tempSprite.setPosition(exitButtonPos);
	this->m_buttons.push_back(tempSprite);
}

//-------------------------------------------------
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

	if (this->m_paused || this->m_wonLevel || this->m_lost)
	{
		// Continue
		if (!this->m_lost)
		{
			if (this->m_buttons[_continueIndex].getGlobalBounds().contains(hoverPos))
				this->m_buttons[_continueIndex].setTexture(*Resources::instance().getGameButtonText(_continueHL));
			else
				this->m_buttons[_continueIndex].setTexture(*Resources::instance().getGameButtonText(_continue));
		}

		// Restart
		if (this->m_buttons[_restartIndex].getGlobalBounds().contains(hoverPos))
			this->m_buttons[_restartIndex].setTexture(*Resources::instance().getGameButtonText(_restartHL));
		else
			this->m_buttons[_restartIndex].setTexture(*Resources::instance().getGameButtonText(_restart));

		// Exit
		if (m_buttons[_exitIndex].getGlobalBounds().contains(hoverPos))
			m_buttons[_exitIndex].setTexture(*Resources::instance().getGameButtonText(_exitButtonHL));
		else
			m_buttons[_exitIndex].setTexture(*Resources::instance().getGameButtonText(_exitButton));
	}
}
//-------------------------------------------------

void Gameplay::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (this->m_paused || this->m_wonLevel || this->m_lost)
	{
		if (!this->m_lost && this->m_buttons[_continueIndex].getGlobalBounds().contains(clickPos))
		{
			if (this->m_wonLevel)
			{
				this->m_wonLevel = false;
				this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl));
			}
			else
				this->m_paused = false;
		}
		else if (this->m_buttons[_restartIndex].getGlobalBounds().contains(clickPos))
		{
			if (this->m_wonLevel)
				this->m_board = Board(this->m_controller->getLevelInfo(--this->m_currLvl));
			else
				this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl));

			this->m_wonLevel = false;
			this->m_lost = false;
			this->m_paused = false;
		}
		else if (this->m_buttons[_exitIndex].getGlobalBounds().contains(clickPos))
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
//-------------------------------------------------