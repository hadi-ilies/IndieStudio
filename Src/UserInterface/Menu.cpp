/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#include "UserInterface/Menu.hpp"
#include <cmath>
/**
 * todo implement types menu
 * types : Selector, Server, Client, Selector2,
**/
//Note : change nbButton by list of button
Menu::Menu(Window *window, const uint &nbButton, const std::string &type)
    : window(window), radius(20), currentButton(0)
{
    if (type == "Selector") {
        for (uint i = 0; i < nbButton; i++) {
            //todo :why just one is displaying
            vector3df pos = getPosButton(i);
            buttonList.push_back(new Button(window, pos));
        }
        scene::ICameraSceneNode* camera = window->getCameraSceneNode(vector3df(radius + 10, 1, 0), vector3df(0, 0, 0));
    }
}

const vector3df Menu::getPosButton(const uint &buttonIndex)
{
    return vector3df(radius * cos(2 * buttonIndex * M_PI / buttonList.size()), 0, radius * sin(2 * buttonIndex * M_PI / buttonList.size()));
}

Menu::~Menu()
{
}

void Menu::turnButtons(const Menu::Dir &direction, const f32 &timestamps)
{
    if (buttonList[0]->animHasFinished()) {
        for (uint i = 0; i < buttonList.size(); i++)
            buttonList[i]->animation(window, getPosButton((i + currentButton + buttonList.size() + direction) % buttonList.size()), timestamps);
        currentButton = (currentButton + buttonList.size() + direction) % buttonList.size();

    }
}

Button *Menu::getButton(const uint &buttonIndex) const
{
    return buttonList[buttonIndex];
}

void Menu::deleteButton(const uint index)
{
    ;
}
