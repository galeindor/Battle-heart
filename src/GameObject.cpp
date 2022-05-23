#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f pos, const int index)
	: m_health(pos), m_isAttacking(false), m_dest(pos), m_isMoving(false), m_target(NULL)
{
	m_sprite.setPosition(pos);
	initSkills(index);
	m_sprite.setTexture(*Resources::instance().getTexture(index));
	auto size = m_sprite.getTexture()->getSize();
	m_sprite.setOrigin(size.x / 2, size.y / 2);
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

float distance(float f1, float f2)
{
	return std::abs(f1 - f2);
}


bool GameObject::checkIntersection() const
{
	if (this->m_target)
	{
		auto tarPos = m_target->getPosition();
		auto myPos = this->getPosition();
		auto range = m_baseAttack->getRange();
		return (distance(tarPos.x, myPos.x) <= range) && (distance(tarPos.y, myPos.y) <= range);
	}
		//return this->m_sprite.getGlobalBounds().intersects(this->m_target->getSprite().getGlobalBounds());

	return false;
}

//=======================================================================================

bool GameObject::checkCollision(const sf::Vector2f& location)
{
	return this->m_sprite.getGlobalBounds().contains(location);
}

//=======================================================================================

bool GameObject::moveValidator()
{
	const auto epsilon = 5.f;
	return (std::abs(m_sprite.getPosition().x - m_dest.x) > epsilon || std::abs(m_sprite.getPosition().y - m_dest.y) > epsilon);
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

void GameObject::update(float deltaTime)
{
	this->updateMovement(deltaTime);
}

//=======================================================================================

void GameObject::initSkills(int index)
{
	auto base = BaseAttack(2.f, BASIC_DMG, 50.f);
	m_baseAttack = std::make_unique<BaseAttack>(base);

	for (int i = 0; i < MAX_SKILL; i++)
	{
		auto skill = Skill(Resources::instance().getSkill(index, i), sf::Vector2f(i * (SKILL_RECT_SIZE + 20) + 30, 30), ATK_CD,BASIC_DMG,5.f);
		m_skills.push_back(std::make_unique<Skill>(skill));
	}
}

//=======================================================================================

void GameObject::useBaseAttack()
{
	m_target->hitCharacter(m_baseAttack->castSkill());
}

//=======================================================================================

void GameObject::useSkill(int index)
{
	m_target->hitCharacter(m_skills[index]->castSkill());
}

//=======================================================================================