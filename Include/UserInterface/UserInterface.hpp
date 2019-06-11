/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#pragma once

#include <vector>
#include <memory>
#include <thread>

#include "Window.hpp"
#include "Menu.hpp"
#include "World.hpp"
#include "JukeBox.hpp"
#include "Entity/Player.hpp"

class UserInterface {
public:
	UserInterface();
	~UserInterface();
    void setBackGround(const std::string &backGround);

public:
    void create(const std::string &backgroundMusic);
    bool demo();
    void run(const vector3df &cameraPos, const vector3df &cameraTarget);

private:
    void checkVolume();
    Menu *createMenuBomberman();
    void linkButtonToMenu();

private:
    Menu *menu;
    Menu *prevMenu;
    scene::ICameraSceneNode *camera;
    float interfaceMusics;
    float interfaceSounds;
    bool lock;
    Player *myPlayer;

};

