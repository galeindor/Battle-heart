#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f pos, const int index)
	: m_isAttacking(false), m_dest(pos), m_isMoving(false), m_target(NULL),
	  m_velocity(sf::Vector2f(0, 0)), m_mass(0.1f), m_maxForce(30), m_maxVelocity(150),
	  m_hpBar(HealthBar(pos))
{
	this->initSkills(index);
	this->initStats(pos, index);

	m_sprite.setPosition(pos);
	m_sprite.setTexture(*Resources::instance().getTexture(index));
	auto size = m_sprite.getTexture()->getSize();
	m_sprite.setOrigin(size.x / 2, size.y);
}

//=======================================================================================

bool GameObject::checkCollision(const sf::Vector2f& location)
{
	return this->m_sprite.getGlobalBounds().contains(location);
}

//=======================================================================================

void GameObject::hitCharacter(int amount)
{
	this->m_stats[_hp]->handleStat(amount);
}

//=======================================================================================

void GameObject::healCharacter(int amount)
{
	this->m_stats[_hp]->handleStat(-amount);
}

//=======================================================================================

void GameObject::update(sf::Vector2f steerForce, float deltaTime)
{
	sf::Vector2f acceleration = steerForce / this->m_mass;
	this->m_velocity = this->m_velocity + acceleration * deltaTime;
	this->m_velocity = this->m_steering->Truncate(this->m_velocity, this->m_maxVelocity);

	if (!this->checkIntersection())
	{
		this->m_isMoving = true;
		this->m_sprite.move(this->m_velocity * deltaTime);
	}
	else
		this->m_isMoving = false;

	// Trim position values to window size
	this->m_sprite.setPosition(this->adjustLocation(this->m_sprite.getPosition()));
	this->m_hpBar.updateHealthBar(m_stats[_hp]->getStat());
	this->m_hpBar.setPosition(this->m_sprite.getPosition());
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

void GameObject::initStats(const sf::Vector2f pos, int index)
{
	for (int index = 0; index < MAX_STATS; index++)
	{
		switch (index)
		{
		case Stats::_hp:
			this->m_stats.push_back(std::make_unique<Stat>(MAX_HEALTH));
		}
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

sf::Vector2f GameObject::adjustLocation(sf::Vector2f location)
{
	auto newLoc = sf::Vector2f();
	newLoc.x = std::min(location.x, float(WINDOW_WIDTH - CUT_CORNERS));
	newLoc.y = std::min(location.y, float(WINDOW_HEIGHT - 1.5f * CUT_CORNERS));

	newLoc.x = std::max(newLoc.x, float(CUT_CORNERS));
	newLoc.y = std::max(newLoc.y, float(HEIGHT_LIMIT));

	return newLoc;
}