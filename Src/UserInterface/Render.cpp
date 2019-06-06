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
    Menu *soloMenu = new Menu(window, vector3df(0, 20, 0), vector3df(20, 0, 0));
    Menu *multiPlayerMenu = new Menu(window, vector3df(0, 40, 0), vector3df(40, 0, 0));
    Menu *settingsMenu = new Menu(window, vector3df(0, 60, 0), vector3df(60, 0, 0));
    Menu *playerMenu = new Menu(window, vector3df(0, 80, 0), vector3df(80, 0, 0));


    soloMenu->addWheel(vector3df(20, 0, 0), 10, {"Stage", "Play", "Back"}); //tmp
    multiPlayerMenu->addWheel(vector3df(40, 0, 0), 10, {"Server", "Client", "Back"}); //tmp
    settingsMenu->addWheel(vector3df(60, 0, 0), 10, {"Sound", "Resolutuion", "Back"}); //tmp
    playerMenu->addWheel(vector3df(80, 0, 0), 10, {"Model1", "Model2", "Model3"}); //tmp
    menu->linkMenu("Solo", soloMenu);
    menu->linkMenu("Multiplayer", multiPlayerMenu);
    menu->linkMenu("Settings", settingsMenu);
    menu->linkMenu("Player", playerMenu);
}

Menu *createMenuBomberman(Window *window)
{
    float radius = 10;
    Menu *menu = new Menu(window, vector3df(0, 0, 0), vector3df(10, 0, 0));
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
            //std::cout << "ZIZI" << std::endl;
            if (menu->getCurrentButtonName() == "Back")
                    menu->linkMenu("Back", menu->getPrevMenu());
            if (!menu->getMenu() && menu->getCurrentButtonName() == "Exit")
                window.close();
            if (!menu->getMenu() && menu->getCurrentButtonName() == "Play") {
                uint port = 8080;
                //server(port, "Resources/Map/Default", 1); have to write in a thread
                //client(IpAddress("127.0.0.1"), port);
            }
            menu->setPrevMenu(menu);
            menu = menu->getMenu();
        }
        window.display();
    }
}