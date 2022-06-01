#pragma once

#include "includeSkill/Skill.h"
#include "includeSkill/BasicAttack.h"
#include "includeSkill/NewSkill.h"
#include "HealthBar.h"
#include "Stat.h"
#include "Object.h"

class Enemy;
class Player;

class Character : public Object
{
public:
	// C-tor/D-tor
	Character(const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime);
	virtual ~Character() = default;

	// Virtuals
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual bool setTarget(std::shared_ptr<Enemy> obj) = 0;
	virtual bool setTarget(std::shared_ptr<Player> obj) = 0;
	virtual bool checkIntersection() const = 0;
	virtual void update(sf::Vector2f steerForce, const float deltaTime);

	// Management
	void showHpBar() { m_hpBar.show(); }
	bool targetInRange() const;

	// Getters
	int getStat(int index)			const		{ return this->m_stats[index]->getStat(); }
	bool getIsAttacking()			const		{ return this->m_isAttacking; }
	HealthBar		getHpBar()		const		{ return this->m_hpBar; }
	Character* getTarget()			const		{ return this->m_target.get(); }
	void setAsTarget(std::shared_ptr<Character> obj) { this->m_target = obj; }

	// Setters
	void setAttacking(bool isAttacking) { this->m_isAttacking = isAttacking; }
	void setStat(int index, int newVal);



protected:
	void setBaseAttack(BaseAttack base) { m_baseAttack = std::make_unique<BaseAttack>(base); }
	//void addSkill(std::unique_ptr<Skill> skill) { m_skills.push_back(skill); }
	//vector<std::unique_ptr<NewSkill>>& getSkills() { return this->m_skills; }
	void useSkill(int index);

private:
	void useBaseAttack();
	void initStats(const int index);
	void initBasic(const int index);

	std::shared_ptr<Character> m_target; // target of basic attack and most of the skills.
	std::unique_ptr<BaseAttack> m_baseAttack; // each character basic attack
	vector<std::unique_ptr<NewSkill>> m_skills; // skills useable
	vector<std::unique_ptr<Stat>> m_stats; // all of the character stats
	HealthBar m_hpBar;
	bool m_isAttacking;
};
