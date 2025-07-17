#include "../../include/menu/Core/SoundManager.h"

SoundManager::SoundManager()
{
	loadSound("choice", "./resources/choice.mp3");
	loadSound("eat", "./resources/eat.mp3");
	loadSound("confirm", "./resources/confirm.mp3");
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

void SoundManager::setVolume(const std::string& name, float volume)
{
	sounds[name]->setVolume(volume);
}