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
	int getStat(int index)			const		{ return this->m_stats[index]->getStat(); }
	bool getIsAttacking()			const		{ return this->m_isAttacking; }
	HealthBar		getHpBar()		const		{ return this->m_hpBar; }

	// Setters
	void setAttacking(bool isAttacking) { this->m_isAttacking = isAttacking; }
	void setStat(int index, int newVal);

	template <class Type>
	std::vector<Target> createTargetVec(Type type);

protected:
	void addSkill(Skill skill) { m_skills.push_back(std::make_unique<Skill>(skill)); }
	//vector<std::unique_ptr<Projectile>>& getSkills() { return this->m_skills; }
	void useSkill(int index);
	// ############# CHECK LATER ##############
	vector<std::shared_ptr<Stat>>& getStats() { return this->m_stats; }

private:
	void useBaseAttack();
	void initStats(const int index);

	void updateSkills(const float deltaTime, 
					  vector<std::shared_ptr<Player>> players,
					  vector<std::shared_ptr<Enemy>> enemies);

	vector<std::unique_ptr<Skill>> m_skills; // skills useable
	vector<std::shared_ptr<Stat>> m_stats; // all of the character stats
	HealthBar m_hpBar;
	bool m_isAttacking;
};
