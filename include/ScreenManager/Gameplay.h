#pragma once
#include "Screen.h"
#include "Board.h"

class Gameplay : public Screen
{
public:
	Gameplay(Controller* controller);
	virtual ~Gameplay() = default;

	// Virtuals
	virtual void init() override;
	virtual void update(const float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;

	//
	bool winLevel();
	void winGame();

protected:
	virtual void initButtons() override;
	virtual void handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	void checkButton(sf::Vector2f hoverPos, GameButtons reg, GameButtons hl, ButtonIndexes index);
	void checkPause(sf::Vector2f hoverPos);
	void cont();
	void restart();
	void exitGame();
	sf::Sprite m_gameState;
	sf::Sprite m_pauseButton;
	vector<sf::Sprite> m_buttons;

	Board m_board;
	bool m_paused = false;
	bool m_continued = false;
	bool m_wonLevel = false;
	bool m_wonGame = false;
	bool m_lost = false;
	bool m_charSelected = false;
	bool m_hoveredPause = false;
	int m_lastButtonHovered = -1;
	unsigned int m_currLvl;
};