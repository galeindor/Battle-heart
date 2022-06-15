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

	enum class VolumeControl
	{
		INC,
		DEC,
		MUTE
	};

	Sound(); // C-tor.
	~Sound() = default; // D-tor.

	// Functions to play/stop music/sound.
	void setSound(Sound::Sounds soundEnum);
	void playSound(int place);
	void playMusic(const std::string fileName);
	void stopMusic();

	// Volume control.
	void setVolume();
	void incVolume();
	void decVolume();
	void muteVolume();

private:
	std::vector<sf::Sound> m_sounds; // Stores the sounds of the game.
	sf::Music m_music; // Used to stream music.
	unsigned int m_volume; // For volume control.
	unsigned int m_prevVolume; // For volume control.
};
