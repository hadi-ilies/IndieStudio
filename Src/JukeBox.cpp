/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** JukeBox.hpp
*/

#include "JukeBox.hpp"
#include "Error.hpp"

JukeBox JukeBox::jukeboxInstance;

/*
 * Constructors // Destructors
 */
JukeBox::JukeBox() : musicVolume(100.0), soundVolume(100.0) {
}

/*
 * Getters // Setters
 */
JukeBox &JukeBox::getInstance() {
    return jukeboxInstance;
}

/*
 * Methods
 */
bool JukeBox::addMusic(const std::string &name, const std::string &fileName) {
    if (musicMap.find(name) != musicMap.end())
        return true;
    if (musicMap[name].openFromFile(fileName)) {
        musicMap[name].setVolume(musicVolume);
        musicMap[name].setLoop(true);
        return true;
    }
    return false;
}

bool JukeBox::addSound(const std::string &name, const std::string &fileName) {
    sf::SoundBuffer buffer;

    if (bufferMap.find(name) != bufferMap.end())
        return true;
    return bufferMap[name].loadFromFile(fileName);
}

void JukeBox::playMusic(const std::string &name) {
    musicMap[name].play();
}

void JukeBox::playSound(const std::string &name) {
    sf::Sound sound;

    deleteEndOfSound();
    sound.setBuffer(bufferMap[name]);
    soundList.push_back(sound);
    soundList.back().setVolume(soundVolume);
    soundList.back().play();
}

void JukeBox::pauseMusic(const std::string &name) {
    musicMap[name].pause();
}

void JukeBox::setVolumeMusic(const float &volume) {
    musicVolume = volume;
    for (auto &it : musicMap)
        it.second.setVolume(volume);
}

void JukeBox::setVolumeSound(const float &volume) {
    soundVolume = volume;
    for (auto &it : soundList)
        it.setVolume(volume);
}

void JukeBox::deleteEndOfSound() {
    for (auto it = soundList.begin() ; it != soundList.end() ;) {
        if (it->getStatus() == sf::SoundSource::Stopped)
            it = soundList.erase(it);
        else
            it++;
    }
}
