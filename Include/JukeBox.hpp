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

public:
    bool addMusic(const std::string &_name, const std::string &_path);
    bool addSound(const std::string &_name, const std::string &_path);
    void playMusic(const std::string &_name);
    void playSound(const std::string &_name);

private:
    void deleteEndedFile();
    static bool isStopped(const sf::Sound &sound);

private:
    std::list<sf::Sound> soundList;
    std::map<std::string, sf::Music> musicMap;
    std::map<std::string, sf::SoundBuffer> bufferMap;
};


#endif /* !BOMBERMAN_JUKEBOX_HPP */
