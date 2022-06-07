#pragma once

#include "Skills/Skill.h"

class BaseAttack : public Skill
{
public:
	BaseAttack(float cooldown, int damage, float range, int wantedStat);

	virtual int castSkill(Stat stat) override;
	void updateBasic(const sf::Vector2f pos, const float deltaTime, bool faceRight);
	void affectWithBasic();
	void drawEffect(sf::RenderWindow& window);
private:
	Effect* m_effect;
};