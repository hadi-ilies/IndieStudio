/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** FontButton.hpp
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
