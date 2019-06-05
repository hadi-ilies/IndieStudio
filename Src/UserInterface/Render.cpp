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

void linkButtonToMenu(Window *window, Menu *menu)
{
    Menu *soloMenu = new Menu(window, vector3df(30 + 10, 1, 0), vector3df(0, 0, 0));
    soloMenu->addWheel(vector3df(10, 0, 0), 30, {"Stage", "Play", "Back"}); //tmp
    menu->linkMenu("Solo", soloMenu);

}

Menu *createMenuBomberman(Window *window)
{
    float radius = 20;
    Menu *menu = new Menu(window, vector3df(radius + 10, 1, 0), vector3df(0, 0, 0));
    menu->addWheel(vector3df(10, 0, 0), radius, {"Solo", "Multiplayer", "Settings", "Player", "Exit"});
    linkButtonToMenu(window, menu);
    return menu;
}

void userInterface()
{
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    Menu *menu = createMenuBomberman(&window);
    window.changeSkybox("Resources/Texture/background.png");

    while (window.isOpen()) {
        if (menu->getKey()) {
             std::cout << "ZIZI" << std::endl;
            menu = menu->getMenu();
        }
        window.display();
    }
}