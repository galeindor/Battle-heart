#include "SteeringInterface.h"

SteeringInterface::SteeringInterface()
{

}


SteeringInterface::~SteeringInterface(){}

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

sf::Vector2f SteeringInterface::Flee(sf::Vector2f object, sf::Vector2f velocity, float maxVelocity, float maxForce, sf::Vector2f target)
{
	sf::Vector2f DesiredVelocity = object - target;
	DesiredVelocity = Normalize(DesiredVelocity);
	DesiredVelocity *= maxVelocity;
	sf::Vector2f SteeringForce = (DesiredVelocity - velocity);
	SteeringForce /= maxVelocity;
	return SteeringForce * maxForce;
}

sf::Vector2f SteeringInterface::Arrive(sf::Vector2f object, sf::Vector2f velocity, float maxVelocity, float maxForce, sf::Vector2f target, float r) 
{
	sf::Vector2f desiredV = target - object;
	sf::Vector2f steeringForce = desiredV - velocity;
	float factor;
	sf::Vector2f dist = desiredV;

	if (length(dist) >= r) {
		//draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 0, 255, 1);
		desiredV = Normalize(desiredV);
		desiredV *= maxVelocity;
		steeringForce /= maxVelocity;
		steeringForce *= maxForce;
	}
	else {
		factor = length(dist) / r;
		//draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 255, 0, 1);
		desiredV *= factor;
	}

	return steeringForce;
}

sf::Vector2f SteeringInterface::Pursue(sf::Vector2f object, sf::Vector2f velocity, float maxVelocity, float maxForce, sf::Vector2f target)
{
	sf::Vector2f desiredV = target - object;
	desiredV = Normalize(desiredV);
	desiredV *= maxVelocity;
	sf::Vector2f steeringForce = desiredV - velocity;
	steeringForce /= maxVelocity;
	steeringForce *= maxForce;

	return steeringForce;
}

sf::Vector2f SteeringInterface::CollisionAvoidance(sf::Vector2f object, sf::Vector2f velocity, float maxVelocity, float maxForce, sf::Vector2f target, std::vector<sf::Vector2f> obstacles, float MAX_AVOID_FORCE)
{
	float v = length(velocity) / maxVelocity;
	sf::Vector2f ahead = object + velocity * v;
	sf::Vector2f halfahead = object + velocity * 0.5f * v;
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

		if (length(distances[i]) <= 50 || length(subdistances[i]) <= 50 || distance(object, obstacles[i]) <= 50) {//50 = radius of sphere


			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);
			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object.x, object.y, avoidForce[i].x, avoidForce[i].y);
			sf::Vector2f desiredV = target - object;
			desiredV = Normalize(desiredV);
			desiredV *= maxVelocity;
			sf::Vector2f steeringForce = desiredV - velocity;
			steeringForce /= maxVelocity;
			steeringForce *= maxForce;
			distances.clear();
			subdistances.clear();

			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);

			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object.x, object.y, ahead.x, ahead.y);


			return steeringForce + avoidForce[i];
		}
		else {

			sf::Vector2f desiredV = target - object;
			desiredV = Normalize(desiredV);
			desiredV *= maxVelocity;
			sf::Vector2f steeringForce = desiredV - velocity;
			steeringForce /= maxVelocity;
			steeringForce *= maxForce;

			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);
			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object.x, object.y, ahead.x, ahead.y);
			return steeringForce;
		}
	}

}


//====================================================================================================
// copy of all functions - using vectors =============================================================


sf::Vector2f SteeringInterface::Flee(std::vector<sf::Vector2f> locations, std::vector<float> values)
{
	sf::Vector2f DesiredVelocity = locations[_object] - locations[_target];
	DesiredVelocity = Normalize(DesiredVelocity);
	DesiredVelocity *= values[_maxVelocity];
	sf::Vector2f SteeringForce = (DesiredVelocity - locations[_velocity]);
	SteeringForce /= values[_maxVelocity];
	return SteeringForce * values[_maxForce];
}

sf::Vector2f SteeringInterface::Arrive(std::vector<sf::Vector2f> vectors, std::vector<float> values, float r)
{
	auto desiredV = vectors[_target] - vectors[_object];
	auto steeringForce = desiredV - vectors[_velocity];
	float factor;
	auto dist = desiredV;

	if (length(dist) >= r) {
		//draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 0, 255, 1);
		desiredV = Normalize(desiredV);
		desiredV *= values[_maxVelocity];
		steeringForce /= values[_maxVelocity];
		steeringForce *= values[_maxForce];
	}
	else {
		factor = length(dist) / r;
		//draw_circle(TheApp::Instance()->getRenderer(), target.x, target.y, r, 0, 255, 0, 1);
		desiredV *= factor;
	}

	return steeringForce;
}

sf::Vector2f SteeringInterface::Pursue(std::vector<sf::Vector2f> vectors, std::vector<float> values)
{
	sf::Vector2f desiredV = vectors[_target] - vectors[_object];
	desiredV = Normalize(desiredV);
	desiredV *= values[_maxVelocity];
	sf::Vector2f steeringForce = desiredV - vectors[_velocity];
	steeringForce /= values[_maxVelocity];
	steeringForce *= values[_maxForce];

	return steeringForce;
}

sf::Vector2f SteeringInterface::CollisionAvoidance(std::vector<sf::Vector2f> vectors,
												   std::vector<sf::Vector2f> obstacles, std::vector<float> values, float MAX_AVOID_FORCE)
{
	float v = length(vectors[_velocity]) / (values[_maxVelocity]);
	sf::Vector2f ahead = vectors[_object] + vectors[_velocity] * v;
	sf::Vector2f halfahead = vectors[_object] + vectors[_velocity] * 0.5f * v;
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

		if (length(distances[i]) <= 50 || length(subdistances[i]) <= 50 || distance(vectors[_object], obstacles[i]) <= 50) {//50 = radius of sphere


			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);
			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object.x, object.y, avoidForce[i].x, avoidForce[i].y);
			sf::Vector2f desiredV = vectors[_target] - vectors[_object];
			desiredV = Normalize(desiredV);
			desiredV *= values[_maxVelocity];
			sf::Vector2f steeringForce = desiredV - vectors[_velocity];
			steeringForce /= values[_maxVelocity];
			steeringForce *= values[_maxForce];
			distances.clear();
			subdistances.clear();

			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);

			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object.x, object.y, ahead.x, ahead.y);


			return steeringForce + avoidForce[i];
		}
		else {

			sf::Vector2f desiredV = vectors[_target] - vectors[_object];
			desiredV = Normalize(desiredV);
			desiredV *= values[_maxVelocity];
			sf::Vector2f steeringForce = desiredV - vectors[_velocity];
			steeringForce /= values[_maxVelocity];
			steeringForce *= values[_maxForce];

			//draw_circle(TheApp::Instance()->getRenderer(), 50, 50, 10, 255, 255, 255, 255);
			//SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), object.x, object.y, ahead.x, ahead.y);
			return steeringForce;
		}
	}

}

//====================================================================================================