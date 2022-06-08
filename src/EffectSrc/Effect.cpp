#include "Effects/Effect.h"

Effect::Effect(const int index)
	: m_animation(Resources::instance().getEffectTexture(index), effectParams),
	  m_timer(Timer(EFFECT_COOLDOWN)), m_draw(false)
{
	this->initSprite(index);
	auto origin = m_sprite.getOrigin();
	m_sprite.setOrigin(origin.x, origin.y - 50);
}

//============================================================================

void Effect::update(const sf::Vector2f pos, const float deltaTime, bool faceRight)
{
	// Checks if the animation is over
	if (this->m_timer.isTimeUp())
		this->m_draw = false;
	else
	{
		this->m_timer.updateTimer(deltaTime);
		// Updates animation
		this->m_sprite.setPosition(pos);
		this->m_animation.setFaceRight(faceRight);
		this->m_animation.update(deltaTime);
		this->m_sprite.setTextureRect(this->m_animation.getUVRect());
	}
}
//============================================================================
/*
void Effect::affect(std::vector<Target> targets)
{
	this->m_time = this->m_cooldown;
	this->m_draw = true;
}
*/

//============================================================================

void Effect::draw(sf::RenderWindow& window)
{
	if(this->m_draw)
		window.draw(this->m_sprite);
}

//============================================================================

void Effect::initSprite(const int index)
{
	this->m_sprite.setPosition(DEFAULT_VEC);
	this->m_sprite.setTexture(*Resources::instance().getEffectTexture(index)); 
	this->m_sprite.setOrigin(m_animation.getUVRect().width / 2, m_animation.getUVRect().height);
}
