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
#include "UserInterface/Wheel.hpp"
#include "UserInterface/MenuElement.hpp"
#include "Window.hpp"

class Menu {
public:
	Menu(Window *window, const std::string name, const vector3df &cameraPos, const vector3df &targetPos);
	~Menu();
    const std::string getName() const;
    std::string getCurrentButtonTexture() const;
    std::string getCurrentButtonModel() const;
    bool linkMenu(const std::string &name, Menu *menu);
    Menu *getMenu();
    bool addWheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttonsNames);
    bool addWheel(const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons);
    bool addButton(const vector3df &position, const std::string &name, const std::string &model, const std::string &texture);
    void setPrevMenu(Menu *menu);
    Menu *getPrevMenu() const;
    const vector3df &getPosition() const;
    const vector3df &getTargetPosition() const;
    bool getKey();
    std::string getCurrentButtonName() const;
private:
    const std::string name;
    const vector3df position;
    const vector3df targetPosition;
    Window *window;
    Menu *prevMenu;
    std::vector<MenuElement *> MenuElements;
    std::map<std::string, Menu *> linkMap;
};

