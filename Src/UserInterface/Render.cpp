/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Render
*/

#include <vector>
#include "Window.hpp"
#include "Error.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp" //?
#include "FormattedSocket.hpp"
#include "UserInterface/Menu.hpp"

using namespace std;
using namespace irr;
using namespace sf;

#include <iostream>
//create menuBomberman that link button to menu by button name
Menu *createMenuBomberman(Window *window)
{
    float radius = 20;
    Menu *menu = new Menu(window, vector3df(radius + 10, 1, 0), vector3df(0, 0, 0));
    menu->addWheel(vector3df(10, 0, 0), radius, {"Solo", "Multiplayer", "Settigs", "Player", "Exit"});
    return menu;
}

void userInterface()
{
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    Menu *menu = createMenuBomberman(&window);
    window.createSkybox("Resources/Block/background/stary-sky.png");

    while (window.isOpen()) {
        menu->getKey();
        window.display(video::SColor(255, 113, 113, 233));
    }
}