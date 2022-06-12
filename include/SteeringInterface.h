#pragma once
#include "macros.h"

class SteeringInterface
{
public:
	SteeringInterface();
	~SteeringInterface();

	float distance(sf::Vector2f start, sf::Vector2f end);
	float length(sf::Vector2f vec);

	sf::Vector2f Normalize(sf::Vector2f vec);

	sf::Vector2f Truncate(const sf::Vector2f& vec, float max);

	// copy of all functions - using vectors =============================================================

	sf::Vector2f Flee(std::vector<sf::Vector2f> locations, std::vector<float> values);

	sf::Vector2f Arrive(std::vector<sf::Vector2f> locations, std::vector<float> values , float r);

	sf::Vector2f Pursue(std::vector<sf::Vector2f> locations, std::vector<float> values);

	sf::Vector2f CollisionAvoidance(std::vector<sf::Vector2f> locations,
									std::vector<sf::Vector2f> obstacles, std::vector<float> values, float MAX_AVOID_FORCE);

	//====================================================================================================

	sf::Vector2f Flee(sf::Vector2f object, sf::Vector2f velocity, 
					  float maxVelocity, float maxForce, sf::Vector2f target);

	sf::Vector2f Arrive(sf::Vector2f object, sf::Vector2f velocity,
						float maxVelocity, float maxForce, sf::Vector2f target, float r);

	sf::Vector2f Pursue(sf::Vector2f object, sf::Vector2f velocity, 
						float maxVelocity, float maxForce, sf::Vector2f target);

	sf::Vector2f CollisionAvoidance(sf::Vector2f object, sf::Vector2f velocity, 
									float maxVelocity, float maxForce, 
									sf::Vector2f target, std::vector<sf::Vector2f> obstacles, float MAX_AVOID_FORCE);
};