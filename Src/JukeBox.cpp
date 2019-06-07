/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** JukeBox.hpp
*/

#include "JukeBox.hpp"
#include "Error.hpp"

bool JukeBox::addMusic(const std::string &_name, const std::string &_path)
{
    return musicMap[_name].openFromFile(_path);
}

bool JukeBox::addSound(const std::string &_name, const std::string &_path)
{
    sf::SoundBuffer buffer;

    return bufferMap[_name].loadFromFile(_path);
}

void JukeBox::playMusic(const std::string &_name)
{
    musicMap[_name].play();
}

void JukeBox::playSound(const std::string &_name)
{
    sf::Sound sound;

    sound.setBuffer(bufferMap[_name]);
    sound.play();
    soundList.push_back(sound);
    deleteEndedFile();
}

void JukeBox::deleteEndedFile()
{
    soundList.remove_if([](const sf::Sound &sound){return sound.getStatus() == sf::SoundSource::Stopped;});
}
