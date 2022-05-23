#pragma once

#include "includeSkill/Skill.h"
#include "includeSkill/BasicAttack.h"
#include "HealthBar.h"
#include "Resources.h"

class Enemy;
class Player;
class Dummy;
class Cleric;
class Knight;

class GameObject
{
public:
	// C-tor/D-tor
	GameObject(const sf::Vector2f pos, const int index);
	virtual ~GameObject() = default;

	// Virtuals
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(const float deltaTime); // NOTE : isn't this function useless?
	virtual bool setTarget(Enemy& obj) = 0;
	virtual bool setTarget(Player& obj) = 0;
	virtual void updateMovement(const float deltaTime) = 0;

	void useBaseAttack();
	void useSkill(int index);
	void move(const float deltaTime);

	// Getters/setters
	int getHp() const { return this->m_health.getHp(); } // get current HP
	sf::Vector2f getPosition() const { return this->m_sprite.getPosition(); }
	bool getIsMoving() const { return this->m_isMoving; }
	void setDestination(sf::Vector2f dest) { this->m_dest = dest; }

	// Checks/validators
	bool checkIntersection() const;
	bool checkCollision(const sf::Vector2f& location);
	bool moveValidator();
	bool collidesWith(const GameObject& obj);

	// Combat mangement
	void hitCharacter(int amount);
	void healCharacter(int amount);

protected:
	// Getters
	HealthBar	getHpBar()  const		{ return this->m_health; }
	sf::Sprite	getSprite() const		{ return this->m_sprite; }
	GameObject* getTarget() const		{ return this->m_target; }
	vector<std::unique_ptr<Skill>>& getSkills() { return this->m_skills; }
	bool getIsAttacking() const { return this->m_isAttacking; }
	sf::Vector2f getDest() const { return this->m_dest; }
	sf::FloatRect getGlobalBounds() const;

	// Setters
	void setAsTarget(GameObject* obj) { this->m_target = obj; }
	void setAttacking(bool isAttacking) { this->m_isAttacking = isAttacking; }
	void setMoving(bool movement) { this->m_isMoving = movement; }

private:
	void initSkills(int index);

	sf::Vector2f m_dest; 
	std::unique_ptr<BaseAttack> m_baseAttack; // each character basic attack
	vector<std::unique_ptr<Skill>> m_skills; // skills useable
	HealthBar m_health;
	sf::Sprite m_sprite;

	bool m_isAttacking;
	bool m_isMoving;

	GameObject* m_target; // target of basic attack and most of the skills.
};
