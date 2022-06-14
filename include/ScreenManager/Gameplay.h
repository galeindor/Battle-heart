#pragma once
#include "Screen.h"
#include "Board.h"
#include "Controller.h"

class Gameplay : public Screen
{
public:
	Gameplay(Controller* controller);
	virtual ~Gameplay() = default;

	//
	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

	//
	bool winLevel();
	void winGame();

protected:
	virtual void initButtons() override;
	virtual void handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;
	
private:
	void checkButton(sf::Vector2f hoverPos, GameButtons reg, GameButtons hl);
	sf::Sprite m_gameState;
	sf::Sprite m_pauseButton;
	// Need to put those 3 in a vector
	// Because they are connected and are lined one after each other
	sf::Sprite m_restartButton;
	sf::Sprite m_exitButton;
	sf::Sprite m_continueButton;
	Board m_board;
	bool m_paused = false;
	bool m_continued = false;
	bool m_wonLevel = false;
	bool m_wonGame = false;
	bool m_lost = false;
	bool m_charSelected = false;
	unsigned int m_currLvl;
};