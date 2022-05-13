#include "..\include\GameObject.h"

GameObject::GameObject(const sf::Vector2f pos, const int index)
	: m_health(pos), m_isAttacking(false)
{
	this->m_sprite.setPosition(pos);

	for (int i = 0; i < MAX_SKILL; i++)
	{
		auto skill = Skill(Resources::instance().getSkill(index, i), sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30) , ATK_CD);
		m_skills.push_back(std::make_unique<Skill>(skill));
	}
}

//=======================================================================================

bool GameObject::checkCollision(const sf::Vector2f& location)
{
	//for (auto& skill : m_skills)
	//	if (skill->checkClick(location))
	//	{
	//		skill->handleClick();
	//		return false;
	//	}

	return this->m_sprite.getGlobalBounds().contains(location);
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

//=======================================================================================

//=======================================================================================

//=======================================================================================