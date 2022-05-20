
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
	setAsTarget((GameObject*)&obj);
	this->setAttacking(true);
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

	if (this->getIsAttacking()) // if not going to attack target
	{
		if (!this->checkIntersection())
			this->move(deltaTime);
		else
		{
			this->setAttacking(false); // player reached his attack target
			this->setDestination(this->getPosition()); 
		}
	}
	else if (this->moveValidator()) // if havent reached the destination 
		this->move(deltaTime);
	else
		moving = false;

	this->setMoving(moving);
}

