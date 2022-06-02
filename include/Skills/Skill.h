#pragma once

#include "Resources.h"
#include "Stat.h"
#include "Effects/Heal.h"

class Character;

class Skill
{
public:
	Skill(float cooldown, int damage, float range , int wantedStat);
	Skill(sf::Texture* texture, const sf::Vector2f& pos, float cooldown , int damage , float range, int wantedStat);
	virtual ~Skill() = default;
	virtual int castSkill(Stat stat) = 0;
	virtual void update();

	int getWantedStat() const { return  m_wantedStat; }

	float getRange() const { return m_skillRange; }
	bool checkClick(const sf::Vector2f& pos);
	void handleClick();
	void draw(sf::RenderWindow& window);
	int getDmg() const { return m_skillDmg; }
	float getCD() const { return m_cooldown; }
	float getTimeLeft() const { return m_timeLeft; }
	void setTimeLeft(float val) { m_timeLeft = val; }

private:

	// skill functionality part 

	int m_wantedStat;
	int m_skillDmg;
	float m_skillRange;
	sf::Clock m_clock;
	float m_cooldown;
	float m_timeLeft;

	// skill visual part
	sf::RectangleShape m_shape; 
	sf::RectangleShape m_cooldownScale;
};

