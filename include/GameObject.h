#pragma once

#include "includeSkill/Skill.h"
#include "includeSkill/BasicAttack.h"
#include "HealthBar.h"
#include "Resources.h"
#include "SteeringInterface.h"
#include "Stat.h"
#include "Animation.h"

class Enemy;
class Player;
class SteeringInterface;

class GameObject
{
public:
	// C-tor/D-tor
	GameObject(const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime);
	virtual ~GameObject() = default;

	// Virtuals
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(sf::Vector2f steerForce, const float deltaTime);
	virtual bool setTarget(Enemy& obj) = 0;
	virtual bool setTarget(Player& obj) = 0;
	virtual bool checkIntersection() const = 0;
	virtual void handleAnimation(sf::Vector2f movement, float deltaTime);

	sf::Vector2f adjustLocation(sf::Vector2f location);

	bool targetInRange() const;

	// Getters
	int getStat(int index)			const		{ return this->m_stats[index]->getStat(); }
	bool getIsMoving()				const		{ return this->m_isMoving; }
	bool getIsAttacking()			const		{ return this->m_isAttacking; }
	sf::Vector2f getPosition()		const		{ return this->m_sprite.getPosition(); }
	sf::Vector2f getVelocity()		const		{ return this->m_velocity; }
	float getMaxVelocity()			const		{ return this->m_maxVelocity; }
	float getMaxForce()				const		{ return this->m_maxForce; }
	SteeringInterface* behaviour()	const		{ return this->m_steering; }
	sf::Vector2f	getDest()		const		{ return this->m_dest; }
	GameObject*		getTarget()		const		{ return this->m_target; }
	HealthBar		getHpBar()		const		{ return this->m_hpBar; }
	sf::Sprite		getSprite()		const		{ return this->m_sprite; }
	sf::FloatRect getGlobalBounds() const		{ return m_sprite.getGlobalBounds(); }

	// Setters
	void setDestination(sf::Vector2f dest) {  this->m_dest = adjustLocation(dest); }
	void setAsTarget(GameObject* obj) { this->m_target = obj; }
	void setAttacking(bool isAttacking) { this->m_isAttacking = isAttacking; }
	void setMoving(bool movement) { this->m_isMoving = movement; }
	void setStat(int index, int newVal) { this->m_stats[index]->setStat(newVal); }

	// Checks/validators
	bool checkCollision(const sf::Vector2f& location);


protected:

	void setBaseAttack(BaseAttack base) { m_baseAttack = std::make_unique<BaseAttack>(base); }
	void addSkill(Skill skill) { m_skills.push_back(std::make_unique<Skill>(skill)); }
	vector<std::unique_ptr<Skill>>& getSkills() { return this->m_skills; }
	virtual void initSkills(int index);

private:

	void useBaseAttack();
	void useSkill(int index);

	void initStats(const sf::Vector2f pos, int index);
	std::unique_ptr<BaseAttack> m_baseAttack; // each character basic attack
	vector<std::unique_ptr<Skill>> m_skills; // skills useable
	vector<std::unique_ptr<Stat>> m_stats; // all of the character stats
	HealthBar m_hpBar;
	sf::Sprite m_sprite;
	bool m_isAttacking;
	bool m_isMoving;

	GameObject* m_target; // target of basic attack and most of the skills.

	// For movement.
	SteeringInterface* m_steering;
	sf::Vector2f m_velocity;
	sf::Vector2f m_dest;

	float m_mass;
	float m_maxForce;
	float m_maxVelocity;

	// For animation.
	Animation m_animation;
	unsigned int m_row;
	float m_speed;
	bool m_faceRight;
	sf::Sprite m_newPosition;
};
