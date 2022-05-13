
#include "Player.h"

Player::Player(const sf::Vector2f loc , int index)
	: m_dest(loc) , m_hpBar(loc), m_isMoving(false) , m_selected(false)
{
	m_sprite.setPosition(loc);
	
	for (int i = 0; i < MAX_SKILL; i++)
	{
		auto skill = Skill(Resources::instance().getSkill(index, i), sf::Vector2f( i * (SKILL_RECT_SIZE+ 20) + 30 , 30 ));
		m_skills.push_back(std::make_unique<Skill>(skill));
	}
}

//==========================================================

void Player::draw(sf::RenderWindow& window)
{
	if (m_selected)
		for (auto& skill : m_skills)
		{
			skill->draw(window); // draw all skills
		}

	m_hpBar.draw(window);
	window.draw(m_sprite);
}

//==========================================================

sf::Vector2f Player::getPosition() const
{
	return m_sprite.getPosition();
}

//==========================================================

bool Player::moveValidator()
{
	const auto epsilon = 1.f;
	return (std::abs(m_sprite.getPosition().x - this->m_dest.x) > epsilon || std::abs(m_sprite.getPosition().y - this->m_dest.y) > epsilon);
}

//==========================================================

void Player::updatePlayer(float deltaTime)
{
	bool moving = true;

	if (this->moveValidator())
		this->movePlayer(deltaTime);
	else
	{
		this->m_sprite.setPosition(this->m_dest);
		moving = false;
	}

	this->m_isMoving = moving;
}

//==========================================================

void Player::movePlayer(float deltaTime)
{
	sf::Vector2f movement = sf::Vector2f(this->m_dest.x - this->m_sprite.getPosition().x, 
										 this->m_dest.y - this->m_sprite.getPosition().y);
	float distance = std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2));
	auto speedPerSecond = 180.f / distance ;
	m_sprite.move(movement * speedPerSecond * deltaTime);
	m_hpBar.setPosition(m_sprite.getPosition());
}

bool Player::handleSkill(sf::Vector2f pos)
{
	for (auto& skill : m_skills) // check for presses
		if (skill->checkClick(pos))
		{
			skill->handleClick();
			return true;
		}

	return false;
}

//==========================================================

bool Player::checkCollision(sf::Vector2f location)
{
	return m_sprite.getGlobalBounds().contains(location);
}