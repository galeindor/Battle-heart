#include "Skills/Skill.h"

#include "Characters/Character.h"

Skill::Skill(sf::Texture* texture, const sf::Vector2f pos, float cooldown,
	const int effectIndex, bool singleTarget, bool onPlayer, bool isActive , float factor)
	: m_timer(Timer(cooldown)), m_singleTarget(singleTarget),
	m_onPlayer(onPlayer), m_isActive(isActive) , m_factor(factor)
{
	this->m_projType = _healBall;
	m_baseValue = 0;
	this->initRect(texture, pos);
	this->initCooldown(pos);
	this->initEffect(effectIndex);
}

//============================================================================

void Skill::updateSkill(float deltaTime, vector<std::shared_ptr<Character>> targets)
{
	if (!this->m_timer.isTimeUp())
	{
		this->setTargets(targets);
		this->m_timer.updateTimer(deltaTime);

		for (int i = 0; i < m_projs.size();)
		{
			//void Projectile::updateProjectile(sf::Vector2f steerForce, float deltaTime)

			this->m_projs[i].updateProjectile(deltaTime);
			if (this->m_projs[i].handleAnimation({ 1,1 }, deltaTime))
			{
				this->m_projs[i] = this->m_projs.back();
				this->m_projs.pop_back();
			}
			else i++;
		}
	}

	for (auto& target : m_targets)
		this->m_effect->update(target->getPosition(), deltaTime, true);
}

//============================================================================

void Skill::useSkill(sf::Vector2f myLoc ,  std::vector<std::shared_ptr<Stat>> myStats)
{
	if (this->m_timer.isTimeUp())
	{
		this->m_timer.setTimer();
		for (auto target : m_targets)
		{
			auto direction = target->getPosition() - myLoc;
			direction = norm(direction);
			auto projectile = Projectile(myLoc, target->getPosition(), this->m_projType, target);
			m_projs.push_back(projectile);
		}
		this->m_effect->affect(m_baseValue, myStats, this->m_targets , m_factor);
	}
}

//============================================================================

sf::Vector2f Skill::norm(sf::Vector2f vec)
{
	float l = std::sqrt(vec.x * vec.x + vec.y * vec.y);
	if (l > 0.0f)
		vec = sf::Vector2f(vec.x / l, vec.y / l);
	else
		vec = sf::Vector2f(0, 0);

	return vec;
}

//============================================================================

void Skill::initEffect(const int effectIndex)
{

	switch (effectIndex)
	{
	case _heal:
		this->m_effect = new Heal(effectParams);
		break;

	case _damage:
		this->m_effect = new Damage(effectParams);
		break;

	case _defend:
		this->m_effect = new Defend(effectParams);
		break;
	default:
		break;
	}
}

//============================================================================

void Skill::initRect(sf::Texture* texture, const sf::Vector2f pos)
{
	m_rect.setTexture(texture);
	m_rect.setPosition(pos);
	m_rect.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE });
}

//============================================================================

void Skill::initCooldown(const sf::Vector2f pos)
{
	m_cooldownScale.setFillColor(sf::Color(0, 0, 0, 200));
	if (m_cooldownScale.getTexture())
		m_cooldownScale.setSize({ SKILL_RECT_SIZE , 0 });
	m_cooldownScale.setPosition(pos);
}

//=============================================================================

void Skill::draw(sf::RenderWindow& window, bool selected)
{
	if (selected)
	{
		updateVisual();
		window.draw(m_rect);
		window.draw(m_cooldownScale);
	}

	for (auto& proj : m_projs)
		proj.draw(window);
}

//==========================================================

void Skill::updateVisual()
{
	m_timer.updateTimer();
	auto timeLeft = m_timer.getTimeLeft();
	timeLeft = std::max(timeLeft, 0.f);
	auto cd = m_timer.getCooldown();
	auto percent = (timeLeft / cd);

	m_cooldownScale.setSize({ SKILL_RECT_SIZE , SKILL_RECT_SIZE * percent });
}

//==========================================================

bool Skill::handleClick(const sf::Vector2f& pos)
{
	auto timeLeft = m_timer.getTimeLeft();
	timeLeft = std::max(timeLeft, 0.f);
	return m_isActive &&(timeLeft == 0.f) && (m_rect.getGlobalBounds().contains(pos));
}
