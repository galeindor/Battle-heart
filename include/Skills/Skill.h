#pragma once
#include "Effects/Effect.h"
#include "Effects/Heal.h"
#include "Effects/Damage.h"
#include "Effects/Defend.h"
#include "Effects/LifeDrain.h"
#include "Timer.h"
#include "Skills/Projectile.h"
#include "HashTable.h"
using std::shared_ptr;
using std::vector;

class Skill
{
public:
	Skill(const sf::Texture* texture, const sf::Vector2f pos, float cooldown,
		const int effectIndex, AttackType type , bool onPlayer, bool isActive , 
		float factor , int projType);
	~Skill() = default;

	// Management
	void updateSkill(float deltaTime, vector<shared_ptr<Character>> targets, vector<shared_ptr<Stat>> myStats);
	void useSkill(sf::Vector2f myLoc);
	void setTargets(vector<shared_ptr<Character>> targets) { this->m_targets = targets; }
	sf::Vector2f norm(sf::Vector2f vec);
	void draw(sf::RenderWindow& window, bool);
	bool handleClick(const sf::Vector2f& loc);
	bool checkHover(sf::Vector2f hoverPos);

	// Getters
	bool getOnPlayer() const { return this->m_onPlayer; }
	AttackType getSkillType() const { return this->m_type; }
	bool getIsActive() const { return this->m_isActive; }
	std::string getInfo() const { return this->m_info; }

private:
	void initInfo(const int effectIndex, const bool onPlayer, 
				  const bool isActive, const float cooldown,
				  AttackType type);
	std::string effectName(const int index);
	std::string targetType(const bool player);
	std::string useType(const bool active);
	std::string cooldownStr(const float cooldown);
	std::string attackType(AttackType type);
	void updateVisual();

	int m_projType;
	Effect* m_effect;
	AttackType m_type;
	bool m_onPlayer;
	bool m_isActive;
	Timer m_timer;
	vector<shared_ptr<Character>> m_targets;
	vector<Projectile> m_projs;
	std::string m_info = "";
	float m_factor;

	// Hash tables
	HashTable<int, string> getTable();
	HashTable<int, string> m_effectsTable;

	// Visuals
	sf::RectangleShape m_rect;
	sf::RectangleShape m_cooldownScale;
	
	// Initiation functions
	void initEffect(const int effectIndex);
	void initRect(const sf::Texture* texture, const sf::Vector2f pos);
	void initCooldown(const sf::Vector2f pos);
};
