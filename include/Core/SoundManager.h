#pragma once

#include <bits/stdc++.h>
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	SoundManager();
	void playSound(const std::string& name);
	void playMusic(const std::string& name);
	void stopMusic(const std::string& name);
	void setVolume(const std::string& name, float volume);
	void setAllSoundsVolume(const float newVolume);
	void setAllMusicVolume(const float newVolume);
	void loadSound(const std::string& name, const std::string& filepath);

private:
	std::map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
	std::map<std::string, std::unique_ptr<sf::Sound>> sounds;
	std::map<std::string, sf::Music> musics;
};

