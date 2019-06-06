/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#include "UserInterface/Menu.hpp"
#include "UserInterface/MenuElement.hpp"
#include "UserInterface/Wheel.hpp"
#include "UserInterface/ButtonElement.hpp"
#include "CameraMove.hpp"

Menu::Menu(Window *window, const vector3df &cameraPos, const vector3df &targetPos)
    : window(window), prevMenu(NULL), position(cameraPos)
{
}

const vector3df &Menu::getPosition() const
{
    return position;
}


//remove back, instead, put an index
#include <iostream>
Menu *Menu::getMenu()
{
    if (linkMap.find(getCurrentButtonName()) != linkMap.end())
        return linkMap[getCurrentButtonName()];
    std::cout << "TEST " << getCurrentButtonName() << std::endl;
    return NULL;
}

std::string Menu::getCurrentButtonName() const
{
    return static_cast<Wheel *>(MenuElements.back())->getCurrentButton()->getName(); //tmp
}

void Menu::setPrevMenu(Menu *menu)
{
    prevMenu = menu;
}

Menu *Menu::getPrevMenu() const
{
    return prevMenu;
}

bool Menu::getKey()
{
    std::cout << getCurrentButtonName() << std::endl;
    if (window->isKeyPressed(KEY_SPACE) || window->isKeyPressed(KEY_RETURN)) {
        return true;
    }
    if (window->isKeyPressed(KEY_RIGHT)) {
        static_cast<Wheel *>(MenuElements.back())->turnButtons(Wheel::RIGHT, 1000);
    }
    else if (window->isKeyPressed(KEY_LEFT)) {
       static_cast<Wheel *>(MenuElements.back())->turnButtons(Wheel::LEFT, 1000);
    }
    return false;
}

bool Menu::linkMenu(const std::string &name, Menu *menu)
{
    linkMap[name] = menu;
}

bool Menu::addWheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttons)
{
    MenuElements.push_back(new Wheel(window, position, radius, buttons));
}

bool Menu::addButton(const vector3df &position, const std::string &name)
{
    MenuElements.push_back(new ButtonElement(window, position, name));
}