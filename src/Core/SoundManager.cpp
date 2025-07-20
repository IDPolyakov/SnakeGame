#include "../../include/Core/SoundManager.h"

SoundManager::SoundManager()
{
	loadSound("choice", "./resources/sounds/choice.mp3");
	loadSound("eat", "./resources/sounds/eat.mp3");
	loadSound("confirm", "./resources/sounds/confirm.mp3");
	musics["backMenuMusic"].openFromFile("./resources/sounds/backMenuMusic.mp3");
	musics["backMenuMusic"].setLooping(true);
	musics["backGameMusic"].openFromFile("./resources/sounds/backGameMusic.mp3");
	musics["backGameMusic"].setLooping(true);
}

void SoundManager::loadSound(const std::string& name, const std::string& filepath)
{
	soundBuffers[name] = std::make_unique<sf::SoundBuffer>(filepath);
	sounds[name] = std::make_unique<sf::Sound>(*soundBuffers[name]);
}

void SoundManager::playSound(const std::string& name)
{
	std::clog << "Played " << name << std::endl;
	sounds[name]->play();
}

void SoundManager::playMusic(const std::string& name)
{
	musics[name].play();
}

void SoundManager::stopMusic(const std::string& name)
{
	musics[name].stop();
}

void SoundManager::setVolume(const std::string& name, float volume)
{
	sounds[name]->setVolume(volume);
}

void SoundManager::setAllSoundsVolume(const float newVolume)
{
	for (auto& [name, sound] : sounds)
		sound->setVolume(newVolume);
}

void SoundManager::setAllMusicVolume(const float newVolume)
{
	for (auto& [name, music] : musics)
		music.setVolume(newVolume);
}