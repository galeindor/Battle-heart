#pragma once
#include "Animation.h"
#include "Resources.h"

class Effect
{
public:
	Effect(sf::Vector2f imageCount, float switchTime, const int index);
	~Effect() = default;

	void update(const sf::Vector2f pos, const float deltaTime, bool faceRight);
	void affect();
	void draw(sf::RenderWindow& window);

	enum Effects
	{
		_heal
	};
private:
	void initSprite(const int index);
	float m_time;
	float m_cooldown;
	bool m_draw;
	sf::Clock m_clock;
	Animation m_animation;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};