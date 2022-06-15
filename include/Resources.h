#pragma once

// ==================== include section ======================

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "macros.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <memory>
#include <queue>
#include <algorithm>
#include <stdlib.h> 
#include <time.h> 
#include "Sound.h"
using std::vector;
using std::list;
using std::string;

// ==========================================================

class Resources
{
public:
	~Resources();
	static Resources& instance();
	const sf::Texture* getBackground(int i)			const { return &m_bgTextures[i]; }
	const sf::Font* getFont()						const { return &m_font; };
	const sf::Texture* getTexture(int i)			const { return &m_textures[i]; }
	const sf::Texture* getProjTexture(int i)		const { return &m_projTextures[i]; }
	const sf::Texture* getLSTexture(int i)			const { return &m_lsTextures[i]; }
	const sf::Texture* getSkillText(int i, int j)	const { return &m_skillTextures[i][j]; }
	const sf::Texture* getGameStateText(int i)		const { return &m_gameStates[i]; }
	const sf::Texture* getGameButtonText(int i)		const { return &m_gameButtonsTextures[i]; }
	const sf::Texture* getVolText(int i)			const { return &m_volTextures[i]; }
	const sf::SoundBuffer* getBuffer(int i)			const { return &m_buffers[i]; }

private:
	Resources();
	Resources(const Resources&) = default;
	sf::Texture m_textures[NUM_OF_OBJECTS];

	sf::Texture m_skillTextures[NUM_OF_PLAYERS][NUM_OF_SKILLS];
	sf::Texture m_bgTextures[NUM_OF_BG];
	sf::Texture m_lsTextures[NUM_OF_LS_TEXTS];
	sf::Texture m_gameStates[NUM_OF_GAME_STATES];
	sf::Texture m_gameButtonsTextures[NUM_OF_GBUTTONS];
	sf::Texture m_projTextures[NUM_OF_PROJ];
	sf::Texture m_volTextures[NUM_OF_VOL_BUTTONS];
	std::vector<sf::SoundBuffer> m_buffers;
	sf::Font m_font;
	void loadResources();
};
