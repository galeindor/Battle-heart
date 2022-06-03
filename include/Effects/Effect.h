#pragma once
#include "Animation.h"
#include "Resources.h"
#include "Stat.h"


class Effect
{
public:
	Effect(const int index);
	~Effect() = default;

	void update(const sf::Vector2f pos, const float deltaTime, bool faceRight);
	void affect(std::vector<Target>  targets);
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