#pragma once
#include "Resources.h"
#include "Screen.h"
#include "Controller.h"

class LevelSelect : public Screen
{
public:
	using Screen::Screen;
	~LevelSelect() = default;

	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;
	void manageRowAndCol(int& row, int& col);


protected:
	virtual void initButtons() override;
	virtual void handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	void destroyButtons();
	bool m_levelHovered = false;
	bool m_levelSelected = false;
	sf::Sprite m_startButton;
	sf::Sprite m_levelSelection;
	sf::Sprite m_levelHover;
	sf::Text m_returnButton;
	std::vector<sf::Sprite> m_availableLevels;
};
