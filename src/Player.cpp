
#include "Player.h"

Player::Player(const sf::Vector2f loc , int index)
	: GameObject(loc, index) , m_selected(false)
{}

//===========================================================

void Player::draw(sf::RenderWindow& window)
{
	if (m_selected)
	{
		this->getHpBar().draw(window);
		for (auto& skill : this->getSkills())
			skill->draw(window); // draw all skills
	}
	window.draw(this->getSprite());
}

//==========================================================

bool Player::checkSkillClick(const sf::Vector2f& location)
{
	for (auto& skill : this->getSkills()) // check for presses on a skill
		if (skill->checkClick(location))
		{
			skill->handleClick();
			return true;
		}
	return false;
}

//==========================================================

bool Player::setTarget(Enemy& obj)
{
	m_target = (GameObject*)&obj;
	return true;
}

//==========================================================

bool Player::setTarget(Player& obj)
{
	return false;
}

//==========================================================

void Player::updateMovement(const float deltaTime)
{
	bool moving = true;

	if ((this->getIsAttacking() && !this->checkIntersection()) ||
		(!this->getIsAttacking() && this->moveValidator()))
		this->move(deltaTime);
	else
		moving = false;

	this->setMovement(moving);
}

