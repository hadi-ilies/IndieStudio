/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** JukeBox.hpp
*/

#ifndef BOMBERMAN_JUKEBOX_HPP
#define BOMBERMAN_JUKEBOX_HPP

#include <SFML/Audio.hpp>
#include <iostream>
#include <utility>

class JukeBox {
public:
    JukeBox(const std::string &_folder);
    ~JukeBox();
public:

private:
    std::string folder;
    std::vector<sf::Music> musicBox;
};


#endif /* !BOMBERMAN_JUKEBOX_HPP */
