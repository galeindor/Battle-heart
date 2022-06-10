#pragma once
#include "Resources.h"
#include "Animation.h"
class Character;

class Projectile1
{
public:
	Projectile1(const sf::Vector2f& pos, const sf::Vector2f direction, 
				const float speed, Projectiles projType,
				std::shared_ptr<Character> target);
	~Projectile1() = default;

	bool update(const float deltaTime);
	bool collidesWithCharacter(sf::Vector2f tarPos);
	void draw(sf::RenderWindow& window) { window.draw(this->m_sprite); }

private:
	Animation m_animation;
	std::shared_ptr<Character> m_target;
	sf::Sprite m_sprite;
	float m_speed;
	sf::Vector2f m_direction;
};