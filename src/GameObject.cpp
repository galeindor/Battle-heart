#include "..\include\GameObject.h"

GameObject::GameObject(const sf::Vector2f pos, const int index)
	: m_health(pos), m_isAttacking(false), m_dest(pos), m_isMoving(false)
{
	this->m_sprite.setPosition(pos);
	this->initSkills(index);
}

//=======================================================================================

void GameObject::move(const float deltaTime)
{
	sf::Vector2f movement = sf::Vector2f(this->m_dest.x - this->m_sprite.getPosition().x,
	this->m_dest.y - this->m_sprite.getPosition().y);
	float distance = std::sqrt(std::pow(movement.x, 2) + std::pow(movement.y, 2));
	auto speedPerSecond = 140.f / distance;
	this->m_sprite.move(movement * speedPerSecond * deltaTime);
	this->m_health.setPosition(this->m_sprite.getPosition());
}

//=======================================================================================

bool GameObject::checkCollision(const sf::Vector2f& location)
{
	
	/*for (auto& skill : m_skills)
		if (skill->checkClick(location))
		{
			skill->handleClick();
			return false;
		}
	*/
	return this->m_sprite.getGlobalBounds().contains(location);
	// note the line above is not good since we want to stop before one is contained in the other
	//return this->m_sprite.getGlobalBounds().intersects(location);

}

//=======================================================================================

bool GameObject::moveValidator()
{
	const auto epsilon = 1.f;
	return (std::abs(this->getSprite().getPosition().x - this->m_dest.x) > epsilon || std::abs(this->getSprite().getPosition().y - this->m_dest.y) > epsilon);
}

//=======================================================================================

void GameObject::hitCharacter(int amount)
{
	this->m_health.lowerHealth(amount); // deal damage to the character
}

//=======================================================================================

void GameObject::healCharacter(int amount)
{
	this->m_health.lowerHealth(-amount); // increase health by lowering negative damage
}


//=======================================================================================
void GameObject::updateMovement(const float deltaTime)
{
	bool moving = true;

	if (this->moveValidator())
		this->move(deltaTime);
	else
	{
		this->m_sprite.setPosition(this->m_dest);
		moving = false;
	}

	this->m_isMoving = moving;
}

//=======================================================================================

void GameObject::initSkills(int index)
{

	for (int i = 0; i < MAX_SKILL; i++)
	{
		auto skill = Skill(Resources::instance().getSkill(index, i), sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30), ATK_CD);
		m_skills.push_back(std::make_unique<Skill>(skill));
	}
}

//=======================================================================================

bool GameObject::setTarget( GameObject& obj)
{
	m_target = &obj;
	return true;
}
//=======================================================================================

//=======================================================================================

//=======================================================================================