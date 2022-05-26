#include "SteeringInterface.h"

SteeringInterface::SteeringInterface()
{

}


SteeringInterface::~SteeringInterface()
{
}

float SteeringInterface::distance(sf::Vector2f start, sf::Vector2f end)
{
	sf::Vector2f v = start - end;
	return length(v);
}

float SteeringInterface::length(sf::Vector2f vec)
{
	auto Rx = vec.x;
	auto Ry = vec.y;
	return std::sqrt(Rx * Rx + Ry * Ry);
}

sf::Vector2f SteeringInterface::Normalize(sf::Vector2f vec)
{
	float l = length(vec);
	if (l > 0.0f)
		return sf::Vector2f(vec.x / l, vec.y / l);
	else
		return sf::Vector2f(0, 0);
}

sf::Vector2f SteeringInterface::Truncate(const sf::Vector2f& vec, float max)
{
	sf::Vector2f truncated = sf::Vector2f(vec.x, vec.y);
	if (length(vec) > max)
		truncated = Normalize(truncated) * max;

	return truncated;
}

sf::Vector2f SteeringInterface::Flee(GameObject* object, sf::Vector2f target)
{
	sf::Vector2f DesiredVelocity = object->getPosition() - target;
	DesiredVelocity = Normalize(DesiredVelocity);
	DesiredVelocity *= object->getMaxVelocity();
	sf::Vector2f SteeringForce = (DesiredVelocity - object->getVelocity());
	SteeringForce /= object->getMaxVelocity();
	return SteeringForce * object->getMaxForce();
}

sf::Vector2f SteeringInterface::Arrive(GameObject* object, sf::Vector2f target, float r) {
	sf::Vector2f desiredV = target - object->getPosition();
	sf::Vector2f steeringForce = desiredV - object->getVelocity();
	float factor;
	sf::Vector2f dist = target - object->getPosition();

	if (length(dist) >= r) {
		//draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 0, 255, 1);
		desiredV = Normalize(desiredV);
		desiredV *= object->getMaxVelocity();
		steeringForce /= object->getMaxVelocity();
		steeringForce *= object->getMaxForce();
	}
	else {
		factor = length(dist) / r;
		//draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 255, 0, 1);
		desiredV *= factor;
	}

	return steeringForce;
}

sf::Vector2f SteeringInterface::Pursue(GameObject* object, sf::Vector2f target)
{
	sf::Vector2f desiredV = target - object->getPosition();
	desiredV = Normalize(desiredV);
	desiredV *= object->getMaxVelocity();
	sf::Vector2f steeringForce = desiredV - object->getVelocity();
	steeringForce /= object->getMaxVelocity();
	steeringForce *= object->getMaxForce();

	return steeringForce;
}

sf::Vector2f SteeringInterface::CollisionAvoidance(GameObject* object, sf::Vector2f target, std::vector<sf::Vector2f> obstacles, float MAX_AVOID_FORCE)
{
	float v = length(object->getVelocity()) / object->getMaxVelocity();
	sf::Vector2f ahead = object->getPosition() + object->getVelocity() * v;
	sf::Vector2f halfahead = object->getPosition() + object->getVelocity() * 0.5f * v;
	std::vector <sf::Vector2f> distances, subdistances, avoidForce;

	for (int i = 0; i < obstacles.size(); i++) {

		sf::Vector2f d = ahead - obstacles[i];
		distances.push_back(d);
		sf::Vector2f subD = halfahead - obstacles[i];
		subdistances.push_back(subD);
		sf::Vector2f af;
		af = ahead - obstacles[i];
		af = Normalize(af) * MAX_AVOID_FORCE;
		avoidForce.push_back(af);


	}
	// Distance and sub distance. ////
	for (int i = 0; i < avoidForce.size(); i++) {

		//draw_circle(TheApp::Instance()->getRenderer(), avoidForce[i].Length(), 50, 10, 255, 255, 255, 255);
		//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 20 * i + 20, distances[i].Length(), 20 * i + 20);
		//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 100, 20 * i + 20, avoidForce[i].Length(), 20 * i + 20);
	}


	for (int i = 0; i < obstacles.size(); i++) {

		if (length(distances[i]) <= 50 || length(subdistances[i]) <= 50 || distance(object->getPosition(), obstacles[i]) <= 50) {//50 = radius of sphere


			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);
			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object->getPosition().x, object->getPosition().y, avoidForce[i].x, avoidForce[i].y);
			sf::Vector2f desiredV = target - object->getPosition();
			desiredV = Normalize(desiredV);
			desiredV *= object->getMaxVelocity();
			sf::Vector2f steeringForce = desiredV - object->getVelocity();
			steeringForce /= object->getMaxVelocity();
			steeringForce *= object->getMaxForce();
			distances.clear();
			subdistances.clear();

			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);

			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object->getPosition().x, object->getPosition().y, ahead.x, ahead.y);


			return steeringForce + avoidForce[i];
		}
		else {

			sf::Vector2f desiredV = target - object->getPosition();
			desiredV = Normalize(desiredV);
			desiredV *= object->getMaxVelocity();
			sf::Vector2f steeringForce = desiredV - object->getVelocity();
			steeringForce /= object->getMaxVelocity();
			steeringForce *= object->getMaxForce();

			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);
			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object->getPosition().x, object->getPosition().y, ahead.x, ahead.y);
			return steeringForce;
		}
	}

}
