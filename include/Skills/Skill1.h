#pragma once
#include "Domains/Domain.h"
#include "Effects/Effect.h"
class Skill1
{
public:
	Skill1(sf::Texture* texture, const sf::Vector2f pos, float cooldown,
		   const int effectIndex, bool singleTarget, bool onPlayer);
	~Skill1() = default;
	void updateSkill(const float deltaTime);
	
	// Getters
	bool getOnPlayer() const { return this->m_onPlayer; }
	bool getSingleTarget() const { return this->m_singleTarget; }

private:
	Domain* m_domain;
	Effect* m_effect;
	bool m_singleTarget;
	bool m_onPlayer;
	float m_cooldown;
	float m_timeLeft;
	// skill visual part
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cooldownScale;

	void initRect(sf::Texture* texture, const sf::Vector2f pos);
	void initCooldown(const sf::Vector2f pos);
};