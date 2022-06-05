
#include "Characters/Player.h"

Player::Player(const sf::Vector2f loc , int index)
	: Character(loc, index, characterParams), m_selected(false)
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
	this->drawEffect(window);
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
	this->addSkill(Skill1(Resources::instance().getSkill(index, 0),
						  sf::Vector2f(0 * (SKILL_RECT_SIZE + 20) + 30, 30),
						  ATK_CD, _heal, singleTarget, onPlayer));
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
	return (norm <= this->getStat(_range));
}

//==========================================================