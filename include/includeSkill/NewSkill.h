#pragma once
#include "Object.h"
#include "SkillDomain.h"
class Character;

class NewSkill : public Object
{
public:
	NewSkill(sf::Texture* texture, float cooldown, const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime);
	NewSkill(float cooldown, const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime);
	~NewSkill() = default;

private:
	sf::Clock m_clock;
	float m_cooldown;
	float m_timeLeft;

	vector<std::shared_ptr<Character>> m_targets;

	// skill visual part
	sf::RectangleShape m_shape;
	sf::RectangleShape m_cooldownScale;
};

