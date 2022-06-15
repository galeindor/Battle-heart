#pragma once

#include "Skills/Projectile.h"
#include "HealthBar.h"
#include "Stat.h"
#include "Object.h"
#include "Skills/Skill.h"
#include "HashTable.h"

class Enemy;
class Player;

class Character : public Object
{
public:
	// C-tor/D-tor
	Character(const sf::Vector2f pos, const int index, AnimationParams animParams);
	virtual ~Character() = default;

	// Virtuals
	virtual bool checkIntersection() const = 0;
	virtual void initSkills(const int index) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) = 0;
	virtual bool setTarget(std::shared_ptr<Player> obj) = 0;
	virtual void update(sf::Vector2f steerForce, const float deltaTime, 
						vector<std::shared_ptr<Player>> m_players, vector<std::shared_ptr<Enemy>> m_enemies);
	// Management
	void showHpBar() { m_hpBar.show(); }
	bool targetInRange() const;

	// Getters
	float				getMoveStat(int index)			const { return m_moveStats[index]; }
	int					getStat(int index)				const { return this->m_stats[index]->getStat(); }
	bool				getIsAttacking()					const { return this->m_isAttacking; }
	bool				isAlive()							const { return this->m_stats[_hp]->getStat() > 0; } // return if the character is alive
	bool				getIsDying()						const { return this->m_isDying; }
	HealthBar			getHpBar()				const { return this->m_hpBar; }
	sf::Vector2f		getVelocity()			const { return this->m_velocity; }
	SteeringInterface*	behaviour()			const { return this->m_steering; }
	std::string getSkillData(int index) const;
	vector<sf::Vector2f> getLocationsVec (bool getDest) const;
	vector<float>		getMoveStats() const { return m_moveStats; }

	// Setters
	void setVelocity(sf::Vector2f velocity) { this->m_velocity = velocity; }
	void setAttacking(bool isAttacking) { this->m_isAttacking = isAttacking; }
	void setStat(int index, int newVal);
	void setDying();
	void setActiveBuff(int index , float duration);

	template <class Type>
	vector<shared_ptr<Character>> createTargetVec(Type type);
	shared_ptr<Character> locateInVector(vector<shared_ptr<Player>> players, vector<shared_ptr<Enemy>> enemies, Character* obj);

	// Skill management
	bool checkSkillClick(const sf::Vector2f& location);
	bool checkSkillHover(sf::Vector2f hoverPos, int index);
	void drawSkills(sf::RenderWindow& window, const bool selected);


protected:
	void createSkill(const int CharIndex, const int skillIndex, const int effectIndex,
		const AttackType single, const bool onPlayer, const bool active, const int projType);
	void addSkill(const Skill skill) { m_skills.push_back(std::make_unique<Skill>(skill)); }

	vector<std::shared_ptr<Stat>>& getStats() { return this->m_stats; }

private:

	void initStats(const int index);
	void initPhysics(const int index);
	void initBuffs();

	void updateSkills(const float deltaTime, 
					  vector<std::shared_ptr<Player>> players,
					  vector<std::shared_ptr<Enemy>> enemies);
	void updateMovement(float deltaTime);
	void updateBuffs();


	vector<std::unique_ptr<Skill>> m_skills; // skills useable
	vector<std::shared_ptr<Stat>> m_stats; // all of the character stats

	// Movement
	SteeringInterface* m_steering;
	sf::Vector2f m_velocity;

	// memebers to handle buffs given to character
	vector < std::pair<Timer, float> > m_buffTimers;
	vector< bool > m_activeBuffs;

	HealthBar m_hpBar;
	bool m_isAttacking;
	bool m_isDying;
	vector<float> m_moveStats;
};
