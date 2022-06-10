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
	Object::update(deltaTime);	
	
	if (!isAlive())
		return;

	sf::Vector2f acceleration = steerForce / this->getMass();
	this->setVelocity(this->getVelocity() + acceleration * deltaTime);
	this->setVelocity(this->behaviour()->Truncate(this->getVelocity(), this->getMaxVelocity()));

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
			this->useBaseAttack();
			if (!handleAnimation(this->getVelocity() * deltaTime, deltaTime))
			{
				this->m_skills[_basic]->handleClick({ 0, 0 });
				this->m_skills[_basic]->useSkill(this->getPosition(), this->m_stats);
			}
		}
		else
			this->setAnimation(_idle);
	}

	// Skills update
	this->updateSkills(deltaTime, m_players, m_enemies);

	this->m_hpBar.updateHealthBar(m_stats[_hp]->getStat());
	this->m_hpBar.setPosition(this->getPosition());
	handleAnimation(this->getVelocity() * deltaTime, deltaTime);
}

//=======================================================================================

void Character::updateSkills(const float deltaTime, vector<std::shared_ptr<Player>> players, vector<std::shared_ptr<Enemy>> enemies)
{
	vector<shared_ptr<Character>> m_targets;
	for (auto& skill : this->m_skills)
	{
		if (skill->getSingleTarget() && this->getTarget())
		{
			m_targets.push_back(locateInVector(players, enemies, this->getTarget()));
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
		this->m_stats.push_back(std::make_shared<Stat>(charactersStats[index][stat]));
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

void Character::createSkill(int charIndex, int& skillIndex, int effectIndex, bool single, bool onPlayer, bool active)
{
	this->addSkill(Skill(Resources::instance().getSkillText(charIndex, skillIndex),
		sf::Vector2f(skillIndex * (SKILL_RECT_SIZE + 20) + 30, 30),
		skillCooldowns[charIndex][skillIndex], effectIndex,
		single, onPlayer, active, skillFactors[charIndex][skillIndex]));

	skillIndex++;
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

void Character::setDying()
{
	this->setAnimation(_death);
	this->m_isDying = true;
	this->m_deathTimer.setTimer();
}

//=======================================================================================

template<class Type>
vector<shared_ptr<Character>> Character::createTargetVec(Type vec)
{
	vector<shared_ptr<Character>> temp;
	for (auto obj : vec)
	{
		temp.push_back(obj);
	}

	return temp;
}

//=======================================================================================

shared_ptr<Character> Character::locateInVector(vector<shared_ptr<Player>> players, vector<shared_ptr<Enemy>> enemies, Character* obj)
{
	for (auto player : players)
	{
		if (player.get() == obj)
			return player;
	}

	for (auto enemy : enemies)
	{
		if (enemy.get() == obj)
			return enemy;
	}

	return nullptr; 
}

//========================================================================================
//========================================================================================

void Character::drawSkills(sf::RenderWindow& window , bool selected)
{
	for (auto& skill : m_skills)
	{
		skill->draw(window,selected);
	}
}

//========================================================================================

bool Character::checkSkillClick(const sf::Vector2f& location)
{
	for (auto& skill : m_skills)
	{
		if (skill->handleClick(location))
		{
			skill->useSkill(this->getPosition(), this->m_stats);
			return true;
		}
	}
	return false;
}