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
#include <boost/filesystem.hpp>
#include <SFML/Audio.hpp>
#include <map>

using namespace boost::filesystem;

class JukeBox {
public:
    JukeBox();
    ~JukeBox();
    const sf::Music &getCurrentMusic() const;
    const sf::Sound &getCurrentSound() const;

public:
    void addMusic(const std::string &_name, const std::string &_path);
    void addSound(const std::string &_name, const std::string &_path);
    void playMusic(const std::string &_name);
    void playSound(const std::string &_name);

private:
    sf::Music currentMusic;
    sf::Sound currentSound;
    std::map<std::string, std::string> musicMap;
    std::map<std::string, std::string> soundMap;
};


#endif /* !BOMBERMAN_JUKEBOX_HPP */
