#include "Resources.h"

Resources::Resources()
{
	this->loadResources();
}

//=======================================================================================

Resources::~Resources(){}

//=======================================================================================

Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}

//======================================================================================

void Resources::loadResources()
{
	for (int i = 0; i < NUM_OF_OBJECTS; i++)
		m_textures[i].loadFromFile(textures[i]);

	for (int i = 0; i < NUM_OF_BG ; i++)
		m_bgTextures[i].loadFromFile(bgTextures[i]);

	for (int i = 0; i < NUM_OF_PLAYERS; i++)
		for (int j = 0; j < NUM_OF_SKILLS; j++)
			m_skillTextures[i][j].loadFromFile(skillTextures[i][j]);

	for (int i = 0; i < NUM_OF_EFFECTS; i++)
		m_effectsTextures[i].loadFromFile(effectsTextures[i]);

	for (int i = 0; i < NUM_OF_LS_TEXTS; i++)
		m_lsTextures[i].loadFromFile(lvSelTexts[i]);

	for (int i = 0; i < NUM_OF_GAME_STATES; i++)
		m_gameStates[i].loadFromFile(gameStateTexts[i]);

	for (int i = 0; i < NUM_OF_GBUTTONS; i++)
		m_gameButtonsTextures[i].loadFromFile(gameButtonsTexts[i]);

	for (int i = 0; i < NUM_OF_PROJ; i++)
		m_projTextures[i].loadFromFile(ProjTextrues[i]);

	for (int i = 0; i < soundList.size(); i++)
	{
		sf::SoundBuffer temp;
		temp.loadFromFile(soundList[i]);
		this->m_buffers.push_back(temp);
	}

	this->m_font.loadFromFile(MAIN_FONT);
}
