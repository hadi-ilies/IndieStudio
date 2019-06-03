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
    ui.getMenu(0).back()->turnButtons(pos, 10.0f);

    while (window.isOpen()) {
        std::cout << window.test->getTarget().X << " " << window.test->getTarget().Y << " " << window.test->getTarget().Z << std::endl;
        //test->getProjectionMatrix();

        window.display(video::SColor(255, 113, 113, 233));
    }
}