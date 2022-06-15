#pragma once
#include "Resources.h"
#include "Screen.h"
#include "Controller.h"

class LevelSelect : public Screen
{
public:
	LevelSelect(Controller* controller);
	~LevelSelect() = default;

	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;
	void manageRowAndCol(int& row, int& col);
	std::string dataToString(const int level);

protected:
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	void initRet();
	void initStart();
	void initHover();
	void initLevelButtons();
	void initlvlDet();
	void destroyButtons();
	virtual void initButtons() override;
	HashTable<int, std::string> getMap();
	HashTable<int, std::string> m_map;
	int m_lastButtonHovered = -1;
	bool m_levelHovered = false;
	bool m_returnHovered = false;
	bool m_startHovered = false;
	bool m_levelSelected = false;
	sf::Sprite m_startButton;
	sf::Sprite m_levelSelection;
	sf::Sprite m_levelHover;
	sf::Text m_returnButton;
	sf::Text m_levelDetails;
	std::vector<sf::Sprite> m_availableLevels;
};
