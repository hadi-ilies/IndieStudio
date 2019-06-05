/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#include "UserInterface/Menu.hpp"
#include "UserInterface/MenuElement.hpp"
#include "UserInterface/Wheel.hpp"

Menu::Menu(Window *window, const vector3df &cameraPos, const vector3df &targetPos)
    :window(window)
{
    scene::ICameraSceneNode* camera = window->getCameraSceneNode(cameraPos, targetPos);//vector3df(radius + 10, 1, 0), vector3df(0, 0, 0));
}

void Menu::getKey()
{
    if (window->isKeyPressed(KEY_SPACE) || window->isKeyPressed(KEY_RETURN)) {
        //   if (menu->select()->type == "menu")
        //       menu = menu->select()->menu;
    }
    if (window->isKeyPressed(KEY_RIGHT)) {
        static_cast<Wheel *>(MenuElements.back())->turnButtons(Wheel::RIGHT, 1000);
    }
    else if (window->isKeyPressed(KEY_LEFT)) {
       static_cast<Wheel *>(MenuElements.back())->turnButtons(Wheel::LEFT, 1000);
    }
}

bool Menu::linkMenu(const std::string &name, Menu *menu)
{
    linkMap[name] = menu;
}

bool Menu::addWheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttons)
{
    MenuElements.push_back(new Wheel(window, position, radius, buttons));
}