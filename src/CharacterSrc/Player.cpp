
#include "Characters/Player.h"

Player::Player(const sf::Vector2f loc , int index)
	: Character(loc, index, characterParams), m_selected(false)
{
	
}

//===========================================================

void Player::draw(sf::RenderWindow& window)
{
	if (m_selected)
		showHpBar();

	drawSkills(window, m_selected);
	getHpBar().draw(window);
	window.draw(this->getSprite());
	//auto bound = this->getSprite().getLocalBounds();
	//auto rect = sf::RectangleShape();
	//rect.setSize({ bound.width, bound.height });
	//rect.setOutlineThickness(3);
	//rect.setFillColor(sf::Color::Transparent);
	//rect.setPosition(this->getPosition());
	//rect.setOrigin(bound.width / 2, bound.height / 2);
	//window.draw(rect);
}

//==========================================================

//==========================================================

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

	auto epsilon = 10.f;
	return norm <= epsilon;
}

//==========================================================