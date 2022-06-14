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
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) = 0;
	virtual bool setTarget(std::shared_ptr<Player> obj) = 0;
	virtual bool checkIntersection() const = 0;
	virtual void update(sf::Vector2f steerForce, const float deltaTime, 
						vector<std::shared_ptr<Player>> m_players, vector<std::shared_ptr<Enemy>> m_enemies);
	// Management
	void showHpBar() { m_hpBar.show(); }
	bool targetInRange() ;

	// Getters
	float	getMoveStat(int index)  const { return m_moveStats[index]; }
	int getStat(int index)			const { return this->m_stats[index]->getStat(); }
	bool isAlive()					const { return this->m_stats[_hp]->getStat() > 0; } // return if the character is alive
	bool getIsAttacking()			const { return this->m_isAttacking; }
	HealthBar		getHpBar()		const { return this->m_hpBar; }
	bool getIsDying()				const { return this->m_isDying; }
	// Setters
	void setAttacking(bool isAttacking) { this->m_isAttacking = isAttacking; }
	void setStat(int index, int newVal);
	void setDying();

	template <class Type>
	vector<shared_ptr<Character>> createTargetVec(Type type);

	shared_ptr<Character> locateInVector(vector<shared_ptr<Player>> players, vector<shared_ptr<Enemy>> enemies , Character* obj);

	// Physics management

	vector<sf::Vector2f> getLocationsVec(bool getDest);
	vector<float> getMoveStats() const { return m_moveStats; }

	sf::Vector2f	getVelocity()			const { return this->m_velocity; }
	void setVelocity(sf::Vector2f velocity) { this->m_velocity = velocity; }
	SteeringInterface* behaviour()			const { return this->m_steering; }

	// Skill management
	virtual void initSkills(const int index) = 0;
	bool checkSkillClick(const sf::Vector2f& location);
	void drawSkills(sf::RenderWindow& window, bool selected);

protected:
	
	void createSkill(int CharIndex, int skillIndex, int effectIndex,
					 bool single, bool onPlayer, bool active, int projType);
	void addSkill(Skill skill) { m_skills.push_back(std::make_unique<Skill>(skill)); }
	void useSkill(int index);
	vector<std::shared_ptr<Stat>>& getStats() { return this->m_stats; }

private:
	void useBaseAttack();
	void initStats(const int index);
	void initPhysics(const int index);

	void updateSkills(const float deltaTime, 
					  vector<std::shared_ptr<Player>> players,
					  vector<std::shared_ptr<Enemy>> enemies);
	void updateMovement(float deltaTime);

	Timer m_deathTimer;
	vector<std::unique_ptr<Skill>> m_skills; // skills useable
	vector<std::shared_ptr<Stat>> m_stats; // all of the character stats

	// Movement
	SteeringInterface* m_steering;
	sf::Vector2f m_velocity;


	HealthBar m_hpBar;
	bool m_isAttacking;
	bool m_isDying;
	vector<float> m_moveStats;
};
