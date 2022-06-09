#pragma once

#include "Skills/Projectile.h"
#include "HealthBar.h"
#include "Stat.h"
#include "Object.h"
#include "Skills/Skill.h"
class Enemy;
class Player;

class Character : public Object
{
public:
	// C-tor/D-tor
	Character(const sf::Vector2f pos, const int index, AnimationParams animParams);
	virtual ~Character() = default;

	// Virtuals
	void drawSkills(sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) = 0;
	virtual bool setTarget(std::shared_ptr<Player> obj) = 0;
	virtual bool checkIntersection() const = 0;
	virtual void update(sf::Vector2f steerForce, const float deltaTime, 
						vector<std::shared_ptr<Player>> m_players, vector<std::shared_ptr<Enemy>> m_enemies);
	virtual void initSkills(const int index) = 0;
	// Management
	void showHpBar() { m_hpBar.show(); }
	bool handleDeath();
	bool targetInRange() ;

	// Getters
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

protected:
	void addSkill(Skill skill) { m_skills.push_back(std::make_unique<Skill>(skill)); }
	void useSkill(int index);
	// ############# CHECK LATER ##############
	vector<std::shared_ptr<Stat>>& getStats() { return this->m_stats; }

	
private:

	void useBaseAttack();
	void initStats(const int index);
	void updateSkills(const float deltaTime, 
					  vector<std::shared_ptr<Player>> players,
					  vector<std::shared_ptr<Enemy>> enemies);

	Timer m_deathTimer;
	vector<std::unique_ptr<Skill>> m_skills; // skills useable
	vector<std::shared_ptr<Stat>> m_stats; // all of the character stats
	HealthBar m_hpBar;
	bool m_isAttacking;
	bool m_isDying;
};
