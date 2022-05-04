#pragma once

// ==================== include section ======================

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "macros.h"

#include <vector>
#include <list>
#include <memory>
#include <queue>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <stdlib.h> 
#include <time.h> 

using std::vector;
using std::list;

// ==========================================================


class Resources
{
public:
	~Resources();
	static Resources& instance();

	sf::Texture* getBackground(int i) { return &m_bgTextures[i]; }
	sf::Font* getFont();
	sf::Texture* getTexture(int i) { return &m_textures[i]; }
	void playSound(int index);
	void setVolume(int volume);
	void setPopOutScreen(sf::RectangleShape& rect , sf::Text& text);
	void initText(sf::Text& text);
	void setAnimation(float deltaTime, sf::Sprite& player, int dir);

private:

	Resources();
	Resources(const Resources&) = default;

	sf::Texture m_textures[NUM_OF_PICS];
	sf::Texture m_bgTextures[NUM_OF_BG];
	void loadTextures();


};