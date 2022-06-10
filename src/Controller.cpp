
#include "Controller.h"
#include "ScreenManager/Gameplay.h"
#include "ScreenManager/Menu.h"

Controller::Controller()
	: m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battle Heart"),
	  m_levelLoader(LevelLoader(LevelsFileName))
{
	this->initScreens();
	m_screens[int(this->m_currentScreen)]->init();
}

//=======================================================================================

void Controller::run()
{
	float deltaTime = 0.f;

	while (this->m_currentScreen != ScreenState::EXIT)
	{
		deltaTime = this->m_clock.restart().asSeconds();
		this->m_window.clear();
		this->swapScreen();
		this->m_screens[int(this->m_currentScreen)]->draw(this->m_window);
		this->m_screens[int(this->m_currentScreen)]->run(this->m_window);
		this->m_window.display();
		this->m_screens[int(this->m_currentScreen)]->update(deltaTime);
	}
}

//=======================================================================================

void Controller::initScreens()
{
	this->m_screens.push_back(std::make_unique<Menu>(this));
	this->m_screens.push_back(std::make_unique<Gameplay>(this));
}

void Controller::swapScreen()
{
    if (this->m_changeScreen)
    {
        m_screens[int(this->m_currentScreen)]->init();

        if (this->m_currentScreen == ScreenState::EXIT)
            exit(EXIT_SUCCESS);

        this->m_changeScreen = false;
    }
}
