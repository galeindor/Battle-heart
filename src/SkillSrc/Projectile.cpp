
#include "Skills/Projectile.h"
#include "Characters/Character.h"

Projectile::Projectile(const sf::Vector2f pos, const sf::Vector2f dest, 
					   const int index, std::shared_ptr<Character> target,
					   AnimationParams params)
	:	Object(pos, index, params, ProjRowlengths[index], 
			   Resources::instance().getProjTexture(index))
{
	setAsTarget(target);
	setAnimation(0);
	auto origin = this->getSprite().getOrigin();
	setOrigin({origin.x -10 , origin.y -20}); // this is a plaster
	setDestination(dest);
}

//==============================================================================

bool Projectile::checkIntersection() const
{
	auto norm = sqrt(pow((this->getPosition().x - this->getDest().x), 2) + pow((this->getPosition().y - this->getDest().y), 2));
	auto epsilon = 10.f;
	return norm <= epsilon || this->getTarget()->checkCollision(this->getPosition());
}

//==============================================================================

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(this->getSprite());
}

//==============================================================================
void Projectile::updateProjectile(sf::Vector2f steerForce,float deltaTime)
{
	this->setDestination(this->getTarget()->getPosition());
	auto dir = this->getPosition() - this->getDest();
	dir = -dir;
	auto speed = 2.1f;
	this->setPosition(this->getPosition()+ speed * dir * deltaTime);
	handleAnimation(this->getVelocity() * deltaTime, deltaTime);
	this->updateOrientation();
	this->setRotation(this->m_orientation);
}

//==============================================================================

void Projectile::updateOrientation()
{
	auto adj = this->getPosition().x - this->getTarget()->getPosition().x;
	auto opp = this->getTarget()->getPosition().y - this->getPosition().y;

	if (opp == 0) opp++;
	if (adj == 0) adj++;
	this->m_orientation = (float)(atan(adj / opp) * RAD2DEG);

	if (opp > 0)
		this->m_orientation += 90;
	else
		this->m_orientation -= 90;

	if (adj > 0)
	{
		this->m_orientation += 180;
		this->setFaceRight(false);
	}
}
