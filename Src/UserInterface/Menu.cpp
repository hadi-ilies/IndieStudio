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
Menu::Menu(Window *window, const uint &nbButton, const std::string &type)
    : window(window)
{
    if (type == "Selector") {
        for (uint i = 0; i < nbButton; i++) {
            //todo :why just one is displaying
            vector3du pos(0, 0, i * 100); //tmp
            buttonList.push_back(unique_ptr<Button>(new Button(window, pos)));
        }
    }
}

Menu::~Menu()
{
}

void Menu::turnButtons(const vector3df &pos, const float &timestamp)
{
    for(auto &button: buttonList) {
        button->animation(window, pos, timestamp);
    }
}
