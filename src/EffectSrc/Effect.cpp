#include "Effects/Effect.h"

Effect::Effect(const int index)
	: m_animation(Resources::instance().getEffectTexture(index), effectParams),
	  m_cooldown(2.f), m_time(0.f), m_draw(false)
{
	this->initSprite(index);
}

void Effect::update(const sf::Vector2f pos, const float deltaTime, bool faceRight)
{
	// Checks if the animation is over
	if (this->m_time < 0.f)
		this->m_draw = false;
	else
	{
		this->m_time -= this->m_clock.restart().asSeconds();
		// Updates animation
		this->m_sprite.setPosition(sf::Vector2f(pos.x, pos.y + 50));
		this->m_animation.setFaceRight(faceRight);
		this->m_animation.update(deltaTime);
		this->m_sprite.setTextureRect(this->m_animation.getUVRect());
	}
}

void Effect::affect(std::vector<Target> targets)
{
	this->m_time = this->m_cooldown;
	this->m_draw = true;
}

void Effect::draw(sf::RenderWindow& window)
{
	if(this->m_draw)
		window.draw(this->m_sprite);
}

void Effect::initSprite(const int index)
{
	this->m_sprite.setPosition(DEFAULT_VEC);
	this->m_sprite.setTexture(*Resources::instance().getEffectTexture(index)); 
	this->m_sprite.setOrigin(m_animation.getUVRect().width / 2, m_animation.getUVRect().height);
}
