/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package UI Package
 * @file ButtonElement
 */

#pragma once

#include <irrlicht/irrlicht.h>

#include "Entity.hpp"
#include "Window.hpp"
#include "Text3d/WordSceneNode.hpp"
#include "UserInterface/AButton.hpp"

class FontButton : public AButton {
public:
    FontButton(Window &window, const vector3df &position, const std::string &name,
               IrrFontBuffer &irrFontBuffer);
    ~FontButton();

public:
    bool animation(const vector3df &destPos, const f32 &timestamps);

private:
    WordSceneNode *button;
};
