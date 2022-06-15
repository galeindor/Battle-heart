#pragma once
#include "Screen.h"
#include "Controller.h"

class Help : public Screen
{
public:
	Help(Controller* controller);
	~Help() = default;

	virtual void update(const float deltaTime) override;
	virtual void init() override;
	virtual void draw(sf::RenderWindow& window) override;

protected:
	virtual void handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window) override;
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) override;

private:
	void initRet();
	sf::Text m_returnButton;
};
