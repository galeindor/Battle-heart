#pragma once

#include "Skill.h"
#include "HealthBar.h"
#include "Resources.h"

class GameObject
{
public:
	GameObject(const sf::Vector2f pos, const int index);
	~GameObject() = default;

	virtual void move(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	sf::Sprite& getSprite() { return this->m_sprite; }
	HealthBar& getHpBar() { return this->m_health; }
	bool checkCollision(sf::Vector2f location);
private:
	vector<std::unique_ptr<Skill>> m_skills;
	HealthBar m_health;
	sf::Sprite m_sprite;
	bool m_isAttacking;
};
