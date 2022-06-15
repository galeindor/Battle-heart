#pragma once
#include "macros.h"

class Enemy;

class SteeringInterface
{
public:
	SteeringInterface();
	~SteeringInterface();


	// copy of all functions - using vectors =============================================================

	sf::Vector2f Flee(std::vector<sf::Vector2f> locations, std::vector<float> values);

	sf::Vector2f Arrive(std::vector<sf::Vector2f> locations, std::vector<float> values , float r);

	sf::Vector2f CollisionAvoidance(std::vector<sf::Vector2f> locations,
									std::vector<sf::Vector2f> obstacles, std::vector<float> values, float MAX_AVOID_FORCE);

	void seperation(Enemy* enemy, std::shared_ptr<Enemy> currEnemy, sf::Vector2f steerForce, float deltaTime);

	float distance(sf::Vector2f start, sf::Vector2f end);
	float length(sf::Vector2f vec);
	sf::Vector2f Normalize(sf::Vector2f vec);
	sf::Vector2f Truncate(const sf::Vector2f& vec, float max);

	//====================================================================================================

};