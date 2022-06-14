#include "Skills/Skill.h"

#include "Characters/Character.h"

Skill::Skill(sf::Texture* texture, const sf::Vector2f pos, float cooldown,
	const int effectIndex, AttackType type, bool onPlayer, bool isActive , float factor , int projType)
	: m_timer(Timer(cooldown)), m_type(type),
	m_onPlayer(onPlayer), m_isActive(isActive) , m_factor(factor)
{
	this->m_projType = projType;
	m_baseValue = 0;
	this->initRect(texture, pos);
	this->initCooldown(pos);
	this->initEffect(effectIndex);
}

//============================================================================

void Skill::updateSkill(float deltaTime, vector<std::shared_ptr<Character>> targets, std::vector<std::shared_ptr<Stat>> myStats)
{
	this->setTargets(targets);
	this->m_timer.updateTimer(deltaTime);

	for (int i = 0; i < m_projs.size(); i++)
	{
		this->m_projs[i].updateMovement(deltaTime);
		if (m_projs[i].checkIntersection())
		{
			this->m_effect->affect(m_baseValue, myStats, m_projs[i].getTarget(), m_factor);
			m_projs.erase(m_projs.begin() + i);
		}
	}
}

//============================================================================

void Skill::useSkill(sf::Vector2f myLoc)
{
	if (this->m_timer.isTimeUp())
	{
		this->m_timer.setTimer();
		for (auto& target : m_targets)
		{
			auto direction = target->getPosition() - myLoc;
			direction = norm(direction);
			AnimationParams projParams = { sf::Vector2f(ProjRowlengths[m_projType][0], 1), 0.3f };
			auto projectile = Projectile(myLoc, target->getPosition(), this->m_projType, target , projParams);
			m_projs.push_back(projectile);
		}
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
	case _drainLife:
		this->m_effect = new LifeDrain(effectParams);
		break;
	case _fear:
		this->m_effect = new Fear(effectParams);
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
	return !m_targets.empty() && m_isActive && (timeLeft == 0.f) && (m_rect.getGlobalBounds().contains(pos));
}

//==========================================================

bool Skill::checkHover(sf::Vector2f hoverPos)
{
	return this->m_rect.getGlobalBounds().contains(hoverPos);
}
