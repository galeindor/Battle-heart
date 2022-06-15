#pragma once
#include "ScreenManager/Screen.h"
#include "Controller.h"

class Menu : public Screen
{
public:
	Menu(Controller* controller);
	~Menu() = default;

	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	
	virtual void handleHover(const sf::Vector2f& hoverPos) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	int m_lastButtonHovered = -1;
	virtual void initButtons() override;
	std::vector<sf::Text> m_buttons;
};
