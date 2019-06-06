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
    Menu *getMenu();
    bool addWheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttons);
    bool addButton(const vector3df &position, const std::string &name);
    void setPrevMenu(Menu *menu);
    Menu *getPrevMenu() const;
    const vector3df &getPosition() const;
    const vector3df &getTargetPosition() const;
    bool getKey();
    std::string getCurrentButtonName() const;
private:
    const vector3df position;
    const vector3df targetPosition;
    Window *window;
    Menu *prevMenu;
    std::vector<MenuElement *> MenuElements;
    std::map<std::string, Menu *> linkMap;
};

