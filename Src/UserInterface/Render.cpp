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
#include "UserInterface/UI.hpp"

using namespace std;
using namespace irr;
using namespace sf;

#include <iostream>
void userInterface()
{
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    Menu mainMenu(&window, 3, "Selector");
    UI ui(&window, &mainMenu);
    vector3df pos(0, 0, 0);
    window.createSkybox("Resources/Block/background/stary-sky.png");
    while (window.isOpen()) {
        if (window.isKeyPressed(KEY_RIGHT)) {
            ui.getMenu(0).back()->turnButtons(Menu::RIGHT, 1000);
        }
        else if (window.isKeyPressed(KEY_LEFT)) {
            ui.getMenu(0).back()->turnButtons(Menu::LEFT, 1000);
        }
        window.display(video::SColor(255, 113, 113, 233));
    }
}