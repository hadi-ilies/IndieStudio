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

Menu::Menu(Window *window, const std::string name, const vector3df &cameraPos, const vector3df &targetPos)
    : window(window), name(name), prevMenu(NULL), position(cameraPos), targetPosition(targetPos)
{
}

const std::string Menu::getName() const
{
    return name;
}


const vector3df &Menu::getPosition() const
{
    return position;
}

const vector3df &Menu::getTargetPosition() const
{
    return targetPosition;
}

#include <iostream>
Menu *Menu::getMenu()
{
    if (linkMap.find(getCurrentButtonName()) != linkMap.end())
        return linkMap[getCurrentButtonName()];
    return NULL;
}

std::string Menu::getCurrentButtonName() const
{
    return static_cast<Wheel *>(MenuElements.back())->getCurrentButton()->getName();
}

std::string Menu::getCurrentButtonTexture() const
{
    return static_cast<Button *> (static_cast<Wheel *>(MenuElements.back())->getCurrentButton())->getTexture();
}

std::string Menu::getCurrentButtonModel() const
{
    return static_cast<Button *> (static_cast<Wheel *>(MenuElements.back())->getCurrentButton())->getModel();
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

bool Menu::addWheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttonsNames)
{
    MenuElements.push_back(new Wheel(window, position, radius, buttonsNames));
}

bool Menu::addWheel(const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons)
{
    MenuElements.push_back(new Wheel(window, position, radius, buttons));
}

bool Menu::addButton(const vector3df &position, const std::string &name, const std::string &model, const std::string &texture)
{
    MenuElements.push_back(new ButtonElement(window, position, name, model, texture));
}