/*
** EPITECH PROJECT, 2019
** FontButton
** File description:
** FontButton
*/

#pragma once

#include <irrlicht/irrlicht.h>

#include "Entity.hpp"
#include "Window.hpp"
#include "Text3d/WordSceneNode.hpp"
#include "UserInterface/AButton.hpp"

class FontButton : public AButton {
public:
    FontButton(const vector3df &position, const std::string &name);
    ~FontButton();

public:
    bool animation(const vector3df &destPos, const f32 &timestamps);

private:
    WordSceneNode *button;
};