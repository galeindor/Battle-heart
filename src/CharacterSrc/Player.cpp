
#include "Characters/Player.h"

Player::Player(const sf::Vector2f loc , int index)
	: Character(loc, index, PlayerParams), m_selected(false)
{
	setScale({ 1.5f , 1.5f });
}

//===========================================================

void Player::draw(sf::RenderWindow& window)
{
	if (m_selected)
		showHpBar();

	drawSkills(window, m_selected);
	getHpBar().draw(window);
	window.draw(this->getSprite());

}

//==========================================================

bool Player::setTarget(std::shared_ptr<Enemy> obj)
{
	setAsTarget(obj);
	this->setAttacking(true);
	return true;
}

//==========================================================

bool Player::setTarget(std::shared_ptr<Player>)
{
	return false;
}

//==========================================================

bool Player::checkIntersection() const
{
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	if (this->getTarget())
		return (norm <= this->getStat(_range));

	const auto epsilon = 10.f;
	return norm <= epsilon;
}

//==========================================================