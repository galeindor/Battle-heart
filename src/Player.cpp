
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


//==========================================================

void Player::update(float deltaTime)
{
	this->updateMovement(deltaTime);
}

//==========================================================


//==========================================================