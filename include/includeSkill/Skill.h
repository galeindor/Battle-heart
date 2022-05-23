#pragma once

#include "Resources.h"

class GameObject;

class Skill
{
public:
	Skill(float cooldown, int damage, float range);
	Skill(sf::Texture* texture, const sf::Vector2f& pos, float cooldown , int damage , float range);
	virtual int castSkill();

	float getRange() const { return m_skillRange; }
	bool checkClick(const sf::Vector2f& pos);
	void handleClick();
	void draw(sf::RenderWindow& window);
	void update();

protected:

	int getDmg() const { return m_skillDmg; }

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

