#include "..\include\GameObject.h"

GameObject::GameObject(const sf::Vector2f pos, const int index)
	: m_health(pos), m_isAttacking(false)
{
	this->m_sprite.setPosition(pos);

	for (int i = 0; i < MAX_SKILL; i++)
	{
		auto skill = Skill(Resources::instance().getSkill(index, i), sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30));
		m_skills.push_back(std::make_unique<Skill>(skill));
	}
}
bool GameObject::checkCollision(sf::Vector2f location)
{
	for (auto& skill : m_skills) // check for presses
		if (skill->checkClick(location))
		{
			skill->handleClick();
			return false;
		}

	return this->m_sprite.getGlobalBounds().contains(location);
}