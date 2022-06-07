#pragma once
#include "Effects/Effect.h"
#include "Effects/Heal.h"
#include "Effects/Damage.h"
#include "Effects/Defend.h"
#include "Timer.h"

class Skill
{
public:
	Skill(sf::Texture* texture, const sf::Vector2f pos, float cooldown,
		  const int effectIndex, bool singleTarget, bool onPlayer, bool isActive);
	~Skill() = default;

	// Management
	void updateSkill(float deltaTime, std::vector<Target> targets);
	void useSkill(std::vector<std::shared_ptr<Stat>> myStats);
	void setTargets(std::vector<Target> targets) { this->m_targets = targets; }

	// Getters
	bool getOnPlayer() const { return this->m_onPlayer; }
	bool getSingleTarget() const { return this->m_singleTarget; }
	bool getIsActive() const { return this->m_isActive; }

private:
	// Settings of the skill
	Effect* m_effect;
	bool m_singleTarget;
	bool m_onPlayer;
	bool m_isActive;
	Timer m_timer;
	std::vector<Target> m_targets = {};
	float m_baseValue;

	// Visuals
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cooldownScale;

	// Initiation functions
	void initEffect(const int effectIndex);
	void initRect(sf::Texture* texture, const sf::Vector2f pos);
	void initCooldown(const sf::Vector2f pos);
};
