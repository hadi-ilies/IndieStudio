/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#pragma once

#include <memory>
#include <vector>
#include <map>
#include "UserInterface/Button.hpp"
#include "UserInterface/MenuElement.hpp"
#include "Window.hpp"

class Menu {
public:
	Menu(Window *window, const vector3df &cameraPos, const vector3df &targetPos);
	~Menu();
    bool linkMenu(const std::string &name, Menu *menu);
    bool addWheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttons);
    void getKey();
private:
    Window *window;
    std::vector<MenuElement *> MenuElements;
    std::map<std::string, Menu *> linkMap;
};

