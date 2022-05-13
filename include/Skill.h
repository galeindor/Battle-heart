#pragma once

#include "Resources.h"

class Skill
{
public:
	Skill(sf::Texture* texture, const sf::Vector2f& pos, float cooldown);
	void castSkill(int index);

	bool checkClick(const sf::Vector2f& pos);
	void handleClick();
	void draw(sf::RenderWindow& window);
	void update();

private:

	// skill functionality part 

	int m_skillDmg;
	float m_skillRange;
	sf::Clock m_clock;
	float m_cooldown;
	float m_timeLeft;

	// skill visual part
	sf::RectangleShape m_shape; 
	sf::RectangleShape m_cooldownScale;
};

