#include "Projectile1.h"
#include "Characters/Character.h"

Projectile1::Projectile1(const sf::Vector2f& pos, const sf::Vector2f direction, 
						 const float speed, int projType, std::shared_ptr<Character> target)
	: m_direction(direction), m_speed(speed), m_target(target),
	  m_animation(Resources::instance().getTexture(int(projType)), projectileParams)
{
	this->initSprite(projType, pos);
}

bool Projectile1::update(const float deltaTime)
{
	this->m_animation.update(deltaTime);
	this->m_sprite.setTextureRect(this->m_animation.getUVRect());
	auto pos = this->m_sprite.getPosition();
	pos += (this->m_direction * this->m_speed * deltaTime);
	this->m_sprite.setPosition(pos);
	return this->collidesWithCharacter(this->m_target->getPosition());
}

bool Projectile1::collidesWithCharacter(sf::Vector2f tarPos)
{
	auto epsilon = 10.f;
	auto posA = this->m_sprite.getPosition() - tarPos;
	auto norm = sqrt(pow((posA.x), 2) + pow((posA.y), 2));
	return norm <= epsilon;
}

void Projectile1::initSprite(int projType, const sf::Vector2f& pos)
{
	this->m_sprite.setPosition(pos);
	//this->m_sprite.setTexture(*Resources::instance().getProjText(projType));
	sf::IntRect size = m_sprite.getTextureRect();
	this->m_sprite.setScale(1.5, 1.5);
	this->m_sprite.setOrigin(size.height / 2, size.width / projectileParams._imageCount.y);
}

