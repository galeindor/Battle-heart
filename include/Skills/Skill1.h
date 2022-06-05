#pragma once
#include "Effects/Effect.h"
#include "Effects/Heal.h"

class Skill1
{
public:
	Skill1(sf::Texture* texture, const sf::Vector2f pos, float cooldown,
		   const int effectIndex, bool singleTarget, bool onPlayer);
	~Skill1() = default;
	void updateSkill(const float deltaTime, std::vector<Target> targets);
	void useSkill(std::vector<std::shared_ptr<Stat>> myStats);
	void setTargets(std::vector<Target> targets) { this->m_targets = targets; }

	// Getters
	bool getOnPlayer() const { return this->m_onPlayer; }
	bool getSingleTarget() const { return this->m_singleTarget; }

private:
	// Settings of the skill
	Effect* m_effect;
	bool m_singleTarget;
	bool m_onPlayer;
	float m_cooldown;
	float m_timeLeft;
	std::vector<Target> m_targets = {};
	sf::Clock m_clock;

	// Visuals
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cooldownScale;

	void initEffect(const int effectIndex);
	void initRect(sf::Texture* texture, const sf::Vector2f pos);
	void initCooldown(const sf::Vector2f pos);
};