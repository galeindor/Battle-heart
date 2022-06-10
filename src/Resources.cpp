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
		m_bgTextures[i].loadFromFile(bg_textures[i]);

	for (int i = 0; i < NUM_OF_PLAYERS; i++)
		for (int j = 0; j < NUM_OF_SKILLS; j++)
			m_skillTextures[i][j].loadFromFile(skillTextures[i][j]);

	for (int i = 0; i < NUM_OF_EFFECTS; i++)
		m_effectsTextures[i].loadFromFile(effectsTextures[i]);

	//for (int i = 0; i < NUM_OF_PROJ; i++)
	//	m_projTextures[i].loadFromFile(proj_textures[i]);

	this->m_buttonsFont.loadFromFile(MENU_BUTTON_FONT);

}

//=======================================================================================

/*
//=======================================================================================
sf::Font* Resources::getFont()
{
	return &m_font;
}

//=======================================================================================
void Resources::loadBuffers()
{
	for (int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		if (!m_buffers[i].loadFromFile(soundBuffers[i]))
			return;
		m_sounds[i].setBuffer(m_buffers[i]);
		m_sounds[i].setVolume(20);
	}
}

//=======================================================================================
void Resources::playSound(int index)
{
	m_sounds[index].play();
}

//=======================================================================================
void Resources::setVolume(int volume)
{
	static bool music_on = true;

	for (int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		m_sounds[i].setVolume(volume);
	}
}

//======================================================================================

sf::Texture* Resources::getScreenTexture(bool victoryFlag)
{
	switch (victoryFlag)
	{
	case State::EnemyEscaped:
		return &m_screenTextures[load_escaped];
	case State::EnemyTrapped:
		return &m_screenTextures[load_trapped];
	default:
		break;
	}
}

//=========================================================================
void Resources::setPopOutScreen(sf::RectangleShape& rect, sf::Text& text)
{

	auto size = sf::Vector2f(WINDOW_WIDTH / 1.5f, WINDOW_HEIGHT / 1.5f);
	rect.setSize(size);
	rect.setOrigin(size.x / 2, size.y / 2);

	auto loc = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	rect.setPosition(loc);
	
	initText(text);
	text.setPosition(loc.x, loc.y + 400);
}
//=======================================================================================
void Resources::initText(sf::Text& text)
{
	text.setCharacterSize(40);
	text.setFont(m_font);
	text.setLetterSpacing(0.8f);
	text.setColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3);

	auto textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	
}

//=======================================================================================

void Resources::setAnimation(float deltaTime, sf::Sprite& player , int dir)
{
	m_animation.update(dir, deltaTime);
	player.setTextureRect(m_animation.uvRect);
	player.setScale(1.5f, 1.5f);
}

//=======================================================================================

*/