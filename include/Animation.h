#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"
// Animation class is in charge of the graphic animations in the game.
class Animation
{
public:
	Animation(sf::Texture* texture, AnimationParams animParams); // C-tor.
	~Animation() = default; // D-tor.

	// Animation management.
	bool update(float deltaTime);
	sf::IntRect& getUVRect() { return this->uvRect; }

	// Setters
	void setRow(int index) { this->m_row = index; }
	void setFaceRight(bool faceRight) { this->m_faceRight = faceRight; }

	// Getters
	bool getFaceRight()	const { return this->m_faceRight; }

private:
	sf::IntRect uvRect; // The rectangle of the currently displayed sprite.
	sf::Vector2f m_imageCount;
	sf::Vector2f m_currentImage;
	float m_totalTime;
	float m_switchTime;
	unsigned int m_row;
	bool m_faceRight;
};