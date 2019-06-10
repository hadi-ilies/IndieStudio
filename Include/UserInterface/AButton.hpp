/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AButton
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <utility>

#include "Utility.hpp"
#include "Entity.hpp"
#include "Window.hpp"

using namespace irr;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class AButton {
public:
    AButton(const vector3df &position, std::string name, std::string type);
    ~AButton();
    const std::string getName() const;
    vector3df getPosition() const;
    bool isAnimationFinished() const;

public:
    virtual bool animation(const vector3df &destPos, const f32 &timestamps) = 0;

protected:
    vector3df position;
    const std::string name;
    ISceneNodeAnimator *anim;

private:
    const std::string type;
};