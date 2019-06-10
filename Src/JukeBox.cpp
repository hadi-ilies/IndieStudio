/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** JukeBox.hpp
*/

#include "JukeBox.hpp"
#include "Error.hpp"

JukeBox JukeBox::jukeboxInstance = JukeBox();

/*
 * Constructors // Destructors
 */
JukeBox::JukeBox() = default;

JukeBox::~JukeBox() = default;

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
    soundList.push_back(sound);
    deleteEndedFile();
}

void JukeBox::deleteEndedFile() {
    soundList.remove_if([](const sf::Sound &sound) { return sound.getStatus() == sf::SoundSource::Stopped; });
}


