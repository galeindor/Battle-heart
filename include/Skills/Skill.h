#pragma once
#include "Effects/Effect.h"
#include "Effects/Heal.h"
#include "Effects/Damage.h"
#include "Effects/Defend.h"
#include "Timer.h"
#include "Skills/Projectile.h"
#include "HashTable.h"
using std::shared_ptr;
using std::vector;

class Skill
{
public:
	Skill(sf::Texture* texture, const sf::Vector2f pos, float cooldown,
		const int effectIndex, bool singleTarget, bool onPlayer, bool isActive);
	~Skill() = default;

	// Management
	void updateSkill(float deltaTime, vector<shared_ptr<Character>> targets);
	void useSkill(sf::Vector2f myLoc, vector<shared_ptr<Stat>> myStats);
	void setTargets(vector<shared_ptr<Character>> targets) { this->m_targets = targets; }

	// Getters
	bool getOnPlayer() const { return this->m_onPlayer; }
	bool getSingleTarget() const { return this->m_singleTarget; }
	bool getIsActive() const { return this->m_isActive; }

	void draw(sf::RenderWindow& window, bool);
	bool handleClick(const sf::Vector2f& loc);
private:

	void updateVisual();

	Projectiles m_projType;
	// Settings of the skill
	Effect* m_effect;
	bool m_singleTarget;
	bool m_onPlayer;
	bool m_isActive;
	Timer m_timer;
	//std::vector<Target> m_targets = {};
	vector<shared_ptr<Character>> m_targets;
	vector<Projectile> m_projs;
	float m_baseValue;

	// Visuals
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cooldownScale;
	
	// Initiation functions
	void initEffect(const int effectIndex);
	void initRect(sf::Texture* texture, const sf::Vector2f pos);
	void initCooldown(const sf::Vector2f pos);
};
