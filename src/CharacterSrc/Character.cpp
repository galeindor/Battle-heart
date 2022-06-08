#include "Characters/Character.h"
#include "Characters/Player.h"
#include "Characters/Enemy.h"

Character::Character(const sf::Vector2f pos, const int index, AnimationParams animParams )
	: m_isAttacking(false), Object(pos, index, animParams), 
	  m_deathTimer(9.f), m_isDying(false)
{
	this->initStats(index);
	m_hpBar = HealthBar(pos, m_stats[_hp]->getStat());
}

//=======================================================================================

void Character::update(sf::Vector2f steerForce, float deltaTime,
					   vector<std::shared_ptr<Player>> m_players, 
					   vector<std::shared_ptr<Enemy>> m_enemies)
{
	this->m_hpBar.updateHealthBar(m_stats[_hp]->getStat());
	this->m_hpBar.setPosition(this->getPosition());
	Object::update(steerForce, deltaTime);		

	sf::Vector2f acceleration = steerForce / this->getMass();
	this->setVelocity(this->getVelocity() + acceleration * deltaTime);
	this->setVelocity(this->behaviour()->Truncate(this->getVelocity(), this->getMaxVelocity()));

	// Skills update
	this->updateSkills(deltaTime, m_players, m_enemies);

	auto target = this->getTarget();
	if (target)
	{
		if (target->isAlive())
			this->setDestination(this->getTarget()->getPosition());
		else
			this->setAsTarget(nullptr);
	}

	if (!this->checkIntersection())
	{
		this->setMoving(true);
		this->setPosition(this->getPosition() + this->getVelocity() * deltaTime);
		this->setAnimation(_walk);
	}
	else
	{
		this->setMoving(false);

		if (targetInRange())
		{
			this->m_skills[_basic]->useSkill(this->getPosition(),this->m_stats);
			this->useBaseAttack();
		}
		else
			this->setAnimation(_idle);
	}
}

//=======================================================================================

void Character::updateSkills(const float deltaTime, vector<std::shared_ptr<Player>> players, vector<std::shared_ptr<Enemy>> enemies)
{
	vector < Character* > m_targets;
	for (auto& skill : this->m_skills)
	{

		if (skill->getSingleTarget() && this->getTarget())
		{
			m_targets.push_back(this->getTarget());
		}
		else if (!skill->getSingleTarget())
		{
			if (skill->getOnPlayer())
				m_targets = this->createTargetVec(players);
			else
				m_targets = this->createTargetVec(enemies);
		}
		
		skill->updateSkill(deltaTime, m_targets);
	}
}

//=======================================================================================

void Character::initStats(const int index)
{
	for (int stat = 0; stat < NUM_OF_STATS; stat++)
		this->m_stats.push_back(std::make_shared<Stat>(playersBasicStats[index][stat]));
}

//=======================================================================================

bool Character::targetInRange() 
{
	if (this->getTarget())
	{
		auto tarPos = this->getTarget()->getPosition();
		auto myPos = this->getPosition();
		auto range = this->getStat(_range);
		auto norm = sqrt(pow(myPos.x - tarPos.x, 2) + pow(myPos.y - tarPos.y, 2));
		return (norm <= range);
		//return (std::abs(tarPos.x - myPos.x) <= range) && (std::abs(tarPos.y - myPos.y) <= range);
	}

	return false;
}

//=======================================================================================

void Character::useBaseAttack()
{
	this->setAnimation(_basicAtt);
}

//=======================================================================================

void Character::useSkill(int skillIndex)
{

}

//=======================================================================================

void Character::setStat(int index, int newVal)
{ 
	if (index == _hp)
		this->showHpBar();
		
	this->m_stats[index]->setStat(newVal); 
}

void Character::setDying()
{
	this->setAnimation(_death);
	this->m_isDying = true;
	this->m_deathTimer.setTimer();
}

//=======================================================================================

template<class Type>
vector < Character* > Character::createTargetVec(Type vec)
{
	vector < Character* > temp;
	for (auto obj : vec)
	{
		temp.push_back(obj.get());
	}

	return temp;
}

//=======================================================================================

bool Character::handleDeath()
{
	this->m_deathTimer.updateTimer();
	return this->m_deathTimer.isTimeUp();
}