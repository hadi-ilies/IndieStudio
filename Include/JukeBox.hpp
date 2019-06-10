/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** JukeBox.hpp
*/

#ifndef JUKEBOX_HPP
#define JUKEBOX_HPP

#include <iostream>
#include <map>
#include <boost/filesystem.hpp>
#include <SFML/Audio.hpp>

using namespace boost::filesystem;

class JukeBox
{
public:
    static JukeBox &getInstance();
    bool addMusic(const std::string &name, const std::string &fileName);
    bool addSound(const std::string &name, const std::string &fileName);
    void playMusic(const std::string &name);
    void playSound(const std::string &name);

private:
    JukeBox& operator=(const JukeBox&){}
    JukeBox(const JukeBox&){}
    JukeBox();
    ~JukeBox();
    void deleteEndedFile();

private:
    static JukeBox jukeboxInstance;
    std::list<sf::Sound> soundList;
    std::map<std::string, sf::Music> musicMap;
    std::map<std::string, sf::SoundBuffer> bufferMap;
};

#endif
