/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#include "UserInterface/Menu.hpp"

/**
 * todo implement types menu
 * types : Selector, Server, Client, Selector2,
**/
//Note : change nbButton by list of button
Menu::Menu(Window *window, const uint &nbButton, const std::string &type)
    : window(window)
{
    if (type == "Selector") {
        for (uint i = 0; i < nbButton; i++) {
            //todo :why just one is displaying
            vector3du pos(0, 0, i * 10); //tmp
            buttonList.push_back(new Button(window, pos));
        }
    }
}

Menu::~Menu()
{
}

void Menu::turnButtons(const vector3df &pos, const f32 &radius)
{
    for(auto &button: buttonList) {
        button->animation(window, pos, radius, 20.f);
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
