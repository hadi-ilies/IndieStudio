/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** JukeBox.hpp
*/

#include <Error.hpp>
#include "JukeBox.hpp"

/*
 *   Constructors // Destructors
 */
JukeBox::JukeBox() = default;

JukeBox::~JukeBox() = default;

/*
 *   Getters // Setters
 */
const sf::Music &JukeBox::getCurrentMusic() const {
    return currentMusic;
}

const sf::Sound &JukeBox::getCurrentSound() const {
    return currentSound;
}

/*
 *   Methods
 */
void JukeBox::addMusic(const std::string &_name, const std::string &_path) {
    musicMap[_name] = _path;
}

void JukeBox::addSound(const std::string &_name, const std::string &_path) {
    soundMap[_name] = _path;
}

void JukeBox::playMusic(const std::string &_name) {
    if (!currentMusic.openFromFile(musicMap[_name]))
        throw Error("failed to load the music " + _name + "(path: " + musicMap[_name] + ")");
    currentMusic.play();
}

void JukeBox::playSound(const std::string &_name) {
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(soundMap[_name]))
        throw Error("failed to load the sound " + _name + "(path: " + soundMap[_name] + ")");
    currentSound.setBuffer(buffer);
    currentSound.play();
}


