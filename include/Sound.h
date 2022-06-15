#pragma once
#include "macros.h"
#include <SFML/Audio.hpp>

// Sound class is in charge of the sounds and music of the game.
class Sound
{
public:
	// Enum for sounds.
	enum class Sounds
	{
		BATTLE,
		BUTTON_CLICK,
		CLICK_PLAYER,
		MOVE_PLAYER,
		HOVER
	};

	// Enum for volume control.
	enum class VolumeControl
	{
		INC,
		DEC,
		MUTE
	};

	Sound(); // C-tor.
	~Sound() = default; // D-tor.

	// Functions to play/stop music/sound.
	void playSound(const int place);
	void playMusic(const std::string fileName);
	void stopMusic();

	// Volume control.
	void incVolume();
	void decVolume();
	void muteVolume();

private:
	// Private methods
	void setSound(const Sound::Sounds soundEnum);
	void setVolume();

	std::vector<sf::Sound> m_sounds; // Stores the sounds of the game.
	sf::Music m_music; // Used to stream music.
	unsigned int m_volume; // For volume control.
	unsigned int m_prevVolume; // For volume control.
};
