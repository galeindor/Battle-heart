#pragma once
#include "Animation.h"
#include "Resources.h"
#include "Stat.h"
#include "Timer.h"

class Effect
{
public:
	Effect(const int index);
	~Effect() = default;

	void update(const sf::Vector2f pos, const float deltaTime, bool faceRight);
	void draw(sf::RenderWindow& window);

	virtual void affect(float baseValue, vector<std::shared_ptr<Stat>> myStats,
						std::vector<Target> targets) = 0;

	enum Effects
	{
		_heal
	};

private:
	void initSprite(const int index);
	Timer m_timer;
	bool m_draw;
	Animation m_animation;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};