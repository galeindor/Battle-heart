#pragma once
#include "Domains/Domain.h"
#include "Effects/Effect.h"
class Skill1
{
public:
	Skill1(std::vector<Target>  domain,
		sf::Texture* texture, const sf::Vector2f pos, float cooldown, int value,
		const int effectIndex);
	~Skill1() = default;
	void updateSkill(const float deltaTime);
private:
	Domain* m_domain;
	Effect* m_effect;
	int m_skillVal;
	float m_cooldown;
	float m_timeLeft;
	// skill visual part
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cooldownScale;

	void initRect(sf::Texture* texture, const sf::Vector2f pos);
	void initCooldown(const sf::Vector2f pos);
};