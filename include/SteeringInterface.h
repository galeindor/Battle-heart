#pragma once
#include "GameObject.h"

class SteeringInterface
{
public:
	SteeringInterface();
	~SteeringInterface();

	float distance(sf::Vector2f start, sf::Vector2f end);
	float length(sf::Vector2f vec);
	sf::Vector2f Normalize(sf::Vector2f vec);
	sf::Vector2f Truncate(const sf::Vector2f& vec, float max);

	sf::Vector2f Seek(GameObject* agent, sf::Vector2f target, float dtime);
	sf::Vector2f Flee(GameObject* agent, sf::Vector2f target, float dtime);
	sf::Vector2f Arrive(GameObject* agent, sf::Vector2f target, float r, float dtime);
	sf::Vector2f Pursue(GameObject* agent, sf::Vector2f target, float maxSpeed, float dtime);
	sf::Vector2f Evade(GameObject* agent, sf::Vector2f target, float maxSpeed, float dtime);
	sf::Vector2f Wander(GameObject* agent, sf::Vector2f target, float dtime);
	sf::Vector2f CollisionAvoidance(GameObject* agent, sf::Vector2f target, std::vector <sf::Vector2f> obstacles, float dtime, float MAX_AHEAD, float MAX_AVOID_FORCE);
};