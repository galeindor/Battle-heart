#include "Characters/Character.h"
#include "Characters/Player.h"
#include "Characters/Enemy.h"

Character::Character(const sf::Vector2f pos, const int index, AnimationParams animParams )
	: m_isAttacking(false), Object(pos, index, animParams)
{
	this->initStats(index);
	m_hpBar= HealthBar(pos, m_stats[_hp]->getStat());
}

//=======================================================================================

void Character::update(sf::Vector2f steerForce, float deltaTime,
					   vector<std::shared_ptr<Player>> m_players, 
					   vector<std::shared_ptr<Enemy>> m_enemies)
{
	this->m_hpBar.updateHealthBar(m_stats[_hp]->getStat());
	this->m_hpBar.setPosition(this->getPosition());
	Object::update(steerForce, deltaTime);

	if (!this->isAlive())
	{
		handleDeath();
		return;
	}



	sf::Vector2f acceleration = steerForce / this->getMass();
	this->setVelocity(this->getVelocity() + acceleration * deltaTime);
	this->setVelocity(this->behaviour()->Truncate(this->getVelocity(), this->getMaxVelocity()));

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
			this->m_skills[_basic]->useSkill(this->m_stats);
			this->useBaseAttack();
		}
		else
			this->setAnimation(_idle);
	}


	// Trim position values to window size and handle animation


}

//=======================================================================================

void Character::updateSkills(const float deltaTime, vector<std::shared_ptr<Player>> players, vector<std::shared_ptr<Enemy>> enemies)
{
	std::vector<Target> m_targets;
	for (auto& skill : this->m_skills)
	{
		if (skill->getSingleTarget() && this->getTarget())
		{
			Target target = { this->getTarget()->getPosition(), this->getTarget()->getStats() };
			m_targets.push_back(target);
		}
		else if (!skill->getSingleTarget())
		{
			if(skill->getOnPlayer())
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

//=======================================================================================

template<class Type>
std::vector<Target> Character::createTargetVec(Type type)
{
	std::vector<Target> temp;
	auto copy = type;
	for (auto obj : copy)
	{
		Target target = { obj.get()->getPosition(), obj.get()->getStats() };
		temp.push_back(target);
	}

	return temp;
}

//=======================================================================================

bool Character::handleDeath()
{
	static auto timer = Timer(1.8f);
	this->setAnimation(_death);
	this->handleAnimation({ 0,0 }, timer.updateTimer());
	
	return timer.isTimeUp();
}