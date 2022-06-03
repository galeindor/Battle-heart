#include "Characters/Character.h"


Character::Character(const sf::Vector2f pos, const int index, AnimationParams animParams )
	: m_isAttacking(false), m_hpBar(HealthBar(pos)), Object(pos, index, animParams)
{
	this->initBasic(index);
	this->initStats(index);
}


//=======================================================================================

void Character::update(sf::Vector2f steerForce, float deltaTime)
{

	sf::Vector2f acceleration = steerForce / this->getMass();
	this->setVelocity(this->getVelocity() + acceleration * deltaTime);
	this->setVelocity(this->behaviour()->Truncate(this->getVelocity(), this->getMaxVelocity()));

	if (!this->checkIntersection())
	{
		this->setMoving(true);
		this->setPosition(this->getPosition() + this->getVelocity() * deltaTime);
		this->setAnimation(_walk);
	}
	else
	{
		this->setMoving(false);
		this->setAnimation(_idle);

		if (targetInRange())
		{
			this->useBaseAttack();
			this->m_baseAttack->affectWithBasic();
		}
	}

	this->m_hpBar.updateHealthBar(m_stats[_hp]->getStat());
	this->m_hpBar.setPosition(this->getPosition());
	// Trim position values to window size and handle animation
	if(this->getTarget())
		setDestination(this->getTarget()->getPosition());
	Object::update(steerForce, deltaTime);

	this->m_baseAttack->update();

	if(targetInRange())
		this->m_baseAttack->updateBasic(this->getPosition(), deltaTime, this->getFaceRight());
	else
		this->m_baseAttack->updateBasic(DEFAULT_VEC, deltaTime, this->getFaceRight());

	//for (auto& skill : this->m_skills)
		//skill->update();
}

//=======================================================================================

void Character::initBasic(const int index)
{
	auto base = BaseAttack(BASE_CD, BASIC_DMG, SHORT_RANGE, _hp);
	setBaseAttack(base);
}

//=======================================================================================

void Character::initStats(const int index)
{
	for (int stat = 0; stat < NUM_OF_STATS; stat++)
	{
		switch (stat)
		{
		case Stats::_hp:
			this->m_stats.push_back(std::make_unique<Stat>(MAX_HEALTH));
			break;

		case Stats::_movementSpeed:
			this->m_stats.push_back(std::make_unique<Stat>(DEFAULT_MVSPD));
			break;

		case Stats::_attackSpeed:
			break;

		case Stats::_range:
			this->m_stats.push_back(std::make_unique<Stat>(m_baseAttack->getRange()));
			break;
		}
	}
}

//=======================================================================================

bool Character::targetInRange() 
{
	if (this->getTarget())
	{
		auto tarPos = this->getTarget()->getPosition();
		auto myPos = this->getPosition();
		auto range = this->getRange();
		if (tarPos.x > myPos.x)
			this->setFaceRight(true);
		else
			this->setFaceRight(false);
		return (std::abs(tarPos.x - myPos.x) <= range) && (std::abs(tarPos.y - myPos.y) <= range);
	}

	return false;
}



//=======================================================================================

void Character::useBaseAttack()
{
	auto index = m_baseAttack->getWantedStat();
	auto dmg = m_baseAttack->castSkill(this->getTarget()->getStat(index));

	if (dmg != 0)
	{
		this->getTarget()->setStat(index, dmg);
	}
	this->setAnimation(_basicAtt);
}

//=======================================================================================

void Character::useSkill(int skillIndex)
{
	auto index = m_baseAttack->getWantedStat();
	//auto dmg = m_skills[skillIndex]->castSkill(this->getTarget()->getStat(index));
	//if (dmg != 0)
		//this->setRow(_basicAtt);

	//this->getTarget()->setStat(index, dmg);
}

//=======================================================================================

void Character::setStat(int index, int newVal)
{ 
	if (index == _hp && getTarget())
		this->getTarget()->showHpBar();
		
	this->m_stats[index]->setStat(newVal); 
}


//=======================================================================================
