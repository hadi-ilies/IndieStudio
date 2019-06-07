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
    //todo remove magic numbers
    Menu *soloMenu = new Menu(window, vector3df(20, 50, 0), vector3df(10, 50, 0));
    Menu *StageMenu = new Menu(window, vector3df(20, 100, 0), vector3df(10, 100, 0));
    Menu *multiPlayerMenu = new Menu(window, vector3df(70, 50, 0), vector3df(60, 50, 0));
    Menu *settingsMenu = new Menu(window, vector3df(20, -100, 0), vector3df(10, -100, 0));
    Menu *playerMenu = new Menu(window, vector3df(20, 500, 0), vector3df(10, 500, 0));

    soloMenu->addWheel(vector3df(0, 50, 0), 10, {{"Stage", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Default.png"}, {"Play", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Back", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}}); //tmp
    StageMenu->addWheel(vector3df(0, 100, 0), 10, {{"Model1", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Model2", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Model3", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}}); //tmp
    multiPlayerMenu->addWheel(vector3df(50, 50, 0), 10, {{"Server", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Default.png"}, {"Client", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Default.png"}, {"Back", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Default.png"}}); //tmp
    settingsMenu->addWheel(vector3df(0, -100, 0), 10, {{"Sound", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Default.png"}, {"Resolution", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Back", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}}); //tmp
    playerMenu->addWheel(vector3df(0, 500, 0), 10, {{"Texture1", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Texture2", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Texture3", "Resources/Entity/Bomberman/Model/Idle.md2", "Texture"}}); //tmp
    soloMenu->linkMenu("Stage", StageMenu);
    menu->linkMenu("Solo", soloMenu);
    menu->linkMenu("Multiplayer", multiPlayerMenu);
    menu->linkMenu("Settings", settingsMenu);
    menu->linkMenu("Player", playerMenu);
    soloMenu->linkMenu("Back", menu);
    multiPlayerMenu->linkMenu("Back", menu);
    settingsMenu->linkMenu("Back", menu);
}

Menu *createMenuBomberman(Window *window)
{
    float radius = 10;
    Menu *menu = new Menu(window, vector3df(20, 0, 0), vector3df(10, 0, 0));
        std::cout << "LOL1" << std::endl;
    menu->addWheel(vector3df(0, 0, 0), radius, {{"Solo", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Multiplayer", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Settings", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Player", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}, {"Exit", "Resources/Entity/Bomberman/Model/Idle.md2", "Resources/Entity/Bomberman/Texture/Dark.png"}});
        std::cout << "LOL2" << std::endl;

    linkButtonToMenu(window, menu);
    return menu;
}

/**todo
 * handle model and texture, chosen
 * handle server and client mode
 * link the demo with the UI
 * add songs, texture
**/

void userInterface()
{
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    Menu *menu = createMenuBomberman(&window);
    window.changeSkybox("Resources/Texture/background.png");
    scene::ICameraSceneNode* camera = window.getCameraSceneNode(vector3df(20, 0, 0), vector3df(10, 0, 0));
    bool lock = false;

    while (window.isOpen()) {
        if (menu->getKey()) {
            if (!lock) {
                if (!menu->getMenu() && menu->getCurrentButtonName() == "Exit")
                    window.close();
                if (!menu->getMenu() && menu->getCurrentButtonName() == "Play") {
                    uint port = 8080;
                    //server(port, "Resources/Map/Default", 1); have to write in a thread
                    //client(IpAddress("127.0.0.1"), port);
                }
                if (menu->getMenu()) {
                    std::cout << menu->getMenu()->getPosition().Y << std::endl;
                    CameraMove cameraAnim(menu->getPosition(), menu->getMenu()->getTargetPosition(), 1);
                    cameraAnim.addPoint(menu->getMenu()->getPosition());
                    window.applyCameraMove(cameraAnim);
                    menu->setPrevMenu(menu);
                    menu = menu->getMenu();
                }
                lock = true;
            }
        }
        else
            lock = false;
        window.display();
    }
}