#pragma once

#include "Skill.h"
#include "HealthBar.h"
#include "Resources.h"

class GameObject
{
public:
	GameObject(const sf::Vector2f pos, const int index);
	~GameObject() = default;

	virtual void move(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::Sprite& getSprite()		{ return this->m_sprite; }
	HealthBar& getHpBar()		{ return this->m_health; }

	bool checkCollision(const sf::Vector2f& location);

	void hitCharacter(int amount);
	void healCharacter(int amount);

private:
	
	HealthBar m_health;
	sf::Sprite m_sprite;
	bool m_isAttacking;

protected:
	vector<std::unique_ptr<Skill>> m_skills;
};
