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
 * Getters // Setters
 */
JukeBox &JukeBox::getInstance() {
    return jukeboxInstance;
}

/*
 * Methods
 */
bool JukeBox::addMusic(const std::string &name, const std::string &fileName) {
    return musicMap[name].openFromFile(fileName);
}

bool JukeBox::addSound(const std::string &name, const std::string &fileName) {
    sf::SoundBuffer buffer;

    return bufferMap[name].loadFromFile(fileName);
}

void JukeBox::playMusic(const std::string &name) {
    musicMap[name].play();
}

void JukeBox::playSound(const std::string &name) {
    sf::Sound sound;

    sound.setBuffer(bufferMap[name]);
    sound.play();
    soundMap[name] = sound;
    deleteEndedFile();
}

void JukeBox::pauseMusic(const std::string &name) {
    musicMap[name].pause();
}

void JukeBox::pauseSound(const std::string &name) {
    soundMap[name].pause();
}

void JukeBox::deleteEndedFile() {
    for (auto it = soundMap.begin() ; it != soundMap.end() ; it++) {
        if(it->second.getStatus() == sf::SoundSource::Stopped)
            soundMap.erase(it);
    }
}
