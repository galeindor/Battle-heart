#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f pos, const int index, sf::Vector2f imageCount, float switchTime)
	: m_isAttacking(false), m_dest(pos), m_isMoving(false), m_target(nullptr),
	  m_velocity(sf::Vector2f(0, 0)), m_mass(0.1f), m_maxForce(30), m_maxVelocity(100),
	  m_hpBar(HealthBar(pos)), m_animation(Resources::instance().getTexture(index), imageCount, switchTime)
{

	m_sprite.setPosition(pos);
	m_sprite.setTexture(*Resources::instance().getTexture(index));
	sf::IntRect size = m_sprite.getTextureRect();
	this->m_sprite.setScale(1.5, 1.5);
	m_sprite.setOrigin(64 / 2, 64);
}

//=======================================================================================

bool GameObject::checkCollision(const sf::Vector2f& location)
{
	return this->m_sprite.getGlobalBounds().contains(location);
}

//=======================================================================================

void GameObject::update(sf::Vector2f steerForce, float deltaTime)
{
	sf::Vector2f acceleration = steerForce / this->m_mass;
	this->m_velocity = this->m_velocity + acceleration * deltaTime;
	this->m_velocity = this->m_steering->Truncate(this->m_velocity, this->m_maxVelocity);

	if (this->getTarget() && !this->targetInRange() )
		this->setDestination(this->getTarget()->getPosition());

	if (!this->checkIntersection())
	{
		this->m_isMoving = true;
		this->m_sprite.move(this->m_velocity * deltaTime);
		this->m_row = _walk;
	}
	else
	{
		this->m_isMoving = false;
		this->m_row = _idle;

		if (targetInRange())
			useBaseAttack();
	}

	// Trim position values to window size and handle animation
	this->handleAnimation(this->m_velocity * deltaTime, deltaTime);
	this->m_sprite.setPosition(this->adjustLocation(this->m_sprite.getPosition()));
	this->m_hpBar.updateHealthBar(m_stats[_hp]->getStat());
	this->m_hpBar.setPosition(this->m_sprite.getPosition());

	this->m_baseAttack->update();

	for (auto skill : m_skills)
	{
		skill->update();
	}

	

}

//======================================================================================

//=======================================================================================

void GameObject::initStats()
{
	for (int index = 0; index < MAX_STATS; index++)
	{
		switch (index)
		{
		case Stats::_hp:
			this->m_stats.push_back(std::make_unique<Stat>(MAX_HEALTH));
			this->m_stats.push_back(std::make_unique<Stat>(m_baseAttack->getRange()));
		}
	}
}

//=======================================================================================

void GameObject::handleAnimation(sf::Vector2f movement, float deltaTime)
{
	// If facing right.
	if (movement.x > 0.0f)
		this->m_faceRight = true;
	else if (movement.x < 0.0f)
		this->m_faceRight = false;

	this->m_animation.update(this->m_row, deltaTime, this->m_faceRight);
	this->m_sprite.setTextureRect(this->m_animation.getUVRect());
}

//=======================================================================================

void GameObject::useBaseAttack()
{
	auto index = m_baseAttack->getWantedStat();
	auto dmg = m_baseAttack->castSkill(m_target->getStat(index));
	if (dmg != 0)
	{
		m_target->setStat(index, dmg);
	}
		m_row = _basicAtt;
}

//=======================================================================================

void GameObject::useSkill(int skillIndex)
{
	auto index = m_baseAttack->getWantedStat();
	auto dmg = m_skills[skillIndex]->castSkill(m_target->getStat(index));
	if (dmg != 0)
		m_row = _basicAtt;
	m_target->setStat(index, dmg);
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

//=======================================================================================
float distance(float f1, float f2)
{
	return std::abs(f1 - f2);
}

//=======================================================================================

bool GameObject::targetInRange() const
{
	if (this->getTarget())
	{
		auto tarPos = m_target->getPosition();
		auto myPos = this->getPosition();
		auto range = m_baseAttack->getRange();
		return (distance(tarPos.x, myPos.x) <= range) && (distance(tarPos.y, myPos.y) <= range);
	}

	return false;
}
