
#include "Player.h"

Player::Player(const sf::Vector2f loc)
	:m_loc(loc) , m_hpBar(loc)
{
	m_sprite.setPosition(loc);
}

//==========================================================

void Player::draw(sf::RenderWindow& window)
{
	m_hpBar.draw(window);
	window.draw(m_sprite);
}

sf::Vector2f Player::getPosition() const
{
	return m_sprite.getPosition();
}

bool Player::moveValidator(sf::Vector2f dest)
{
	const auto epsilon = 1.f;
	return (std::abs(m_sprite.getPosition().x - dest.x) > epsilon || std::abs(m_sprite.getPosition().y - dest.y) > epsilon);
}

void Player::movePlayer(sf::Vector2f direction, float delta)
{
	auto speedPerSecond = 0.5f;
	m_sprite.move(direction * speedPerSecond * delta);
	m_hpBar.setPosition(m_sprite.getPosition());
}
