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

/*
 *   Methods
 */
bool JukeBox::addMusic(const std::string &_name, const std::string &_path) {
    return musicMap[_name].openFromFile(_path);
}

bool JukeBox::addSound(const std::string &_name, const std::string &_path) {
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile(_path))
        return false;
    soundMap[_name].setBuffer(buffer);
}

void JukeBox::playMusic(const std::string &_name) {
    musicMap[_name].play();
}

void JukeBox::playSound(const std::string &_name) {
    soundMap[_name].play();
}


