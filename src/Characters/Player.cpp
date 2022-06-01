
#include "includeCharacter/Player.h"

Player::Player(const sf::Vector2f loc , int index)
	: Character(loc, index, sf::Vector2f(9, 5), 0.3f) , m_selected(false)
{
	this->initSkills(index);
}

//===========================================================

void Player::draw(sf::RenderWindow& window)
{
	if (m_selected)
	{
		showHpBar();
		/*
		for (auto& skill : this->getSkills())
			skill->draw(window); // draw all skills
			*/
	}
	getHpBar().draw(window);
	window.draw(this->getSprite());
}

//==========================================================

bool Player::checkSkillClick(const sf::Vector2f& location)
{
	/*
	auto skills = getSkills();
	for (size_t i = 0; i < skills.size(); i++)
	{
		if (skills[i]->checkClick(location))
		{
			this->useSkill(i);
			return true;
		}
	}
	*/
	return false;
}

void Player::initSkills(const int index)
{
	//for(int i = 0; i < MAX_SKILL; i++)

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
	const auto epsilon = 10.f;
	return (std::abs(this->getSprite().getPosition().x - this->getDest().x) < epsilon || std::abs(this->getSprite().getPosition().y - this->getDest().y) < epsilon);
}

//==========================================================