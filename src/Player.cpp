
#include "Player.h"

Player::Player(const sf::Vector2f loc , int index)
	: GameObject(loc, index), m_dest(loc) , m_isMoving(false) , m_selected(false)
{
	
}
//==========================================================
void Player::draw(sf::RenderWindow& window)
{
	if (m_selected)
		//here was the loop
	this->getHpBar().draw(window);
	window.draw(this->getSprite());
}
//==========================================================


//==========================================================

bool Player::moveValidator()
{
	const auto epsilon = 1.f;
	return (std::abs(this->getSprite().getPosition().x - this->m_dest.x) > epsilon || std::abs(this->getSprite().getPosition().y - this->m_dest.y) > epsilon);
}

//==========================================================

void Player::updatePlayer(float deltaTime)
{
	bool moving = true;

	if (this->moveValidator())
		this->move(deltaTime);
	else
	{
		this->getSprite().setPosition(this->m_dest);
		moving = false;
	}

	this->m_isMoving = moving;
}

//==========================================================

void Player::move(float deltaTime)
{
	sf::Vector2f movement = sf::Vector2f(this->m_dest.x - this->getSprite().getPosition().x, 
										 this->m_dest.y - this->getSprite().getPosition().y);
	float distance = std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2));
	auto speedPerSecond = 180.f / distance ;
	this->getSprite().move(movement * speedPerSecond * deltaTime);
	this->getHpBar().setPosition(this->getSprite().getPosition());
}

//==========================================================

