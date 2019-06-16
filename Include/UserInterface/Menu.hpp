/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Menu.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include <map>

#include "UserInterface/Wheel.hpp"
#include "UserInterface/MenuElement.hpp"
#include "UserInterface/ButtonElement.hpp"
#include "Window.hpp"
#include "CameraMove.hpp"

class Menu
{
public:
    Menu(Window &_window, IrrFontBuffer &irrFontBuffer, std::string name, const vector3df &cameraPos, const vector3df &targetPos);
    ~Menu();
    const std::string getName() const;
    std::string getCurrentButtonTexture() const;
    std::string getCurrentButtonModel() const;
    Menu *getMenu();
    void setPrevMenu(Menu *menu);
    Menu *getPrevMenu() const;
    const vector3df &getPosition() const;
    const vector3df &getTargetPosition() const;
    bool getKey();
    std::string getCurrentButtonName() const;
    Menu *getMenuFromName(const std::string &_name);

public:
    void linkMenu(const std::string &name, Menu *menu);
    void addWheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttonsNames);
    void addWheel(const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons);
    void addButton(const vector3df &position, const std::string &name, const std::string &model, const std::string &texture);


private:
    Window &window;
    IrrFontBuffer &irrFontBuffer;
    const std::string name;
    const vector3df position;
    const vector3df targetPosition;
    Menu *prevMenu;
    std::vector<MenuElement *> MenuElements;
    std::map<std::string, Menu *> linkMap;
};
