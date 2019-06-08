/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#pragma once

#include <vector>
#include <memory>
#include "Window.hpp"
#include "Menu.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp" //?
#include "FormattedSocket.hpp"

class UserInterface {
public:
	UserInterface(Window *window);
	~UserInterface();
    void setBackGround(const std::string &backGround);
    void create();
    bool demo();
    void run(const vector3df &cameraPos, const vector3df &cameraTarget);
private:
    Menu *createMenuBomberman(Window *window);
    void linkButtonToMenu(Window *window, Menu *menu);
private:
    Window *window;
    Menu *menu;
    scene::ICameraSceneNode *camera;
    bool lock;
    Player *myPlayer;

};

