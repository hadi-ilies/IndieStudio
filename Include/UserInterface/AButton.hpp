/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package UI Package
 * @file AButton
 * @see Button.cpp
 * @see FontButton.cpp
 */

#pragma once

#include <irrlicht/irrlicht.h>
#include <utility>

#include "Utility.hpp"
#include "Entity.hpp"
#include "Window.hpp"

/**
 * @namespace Irrlicht
 */
using namespace irr;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class AButton {
public:
    AButton(Window &_window, const vector3df &position, std::string name, std::string type);
    virtual ~AButton();
    const std::string getName() const;
    vector3df getPosition() const;
    bool isAnimationFinished() const;

public:
    virtual bool animation(const vector3df &destPos, const f32 &timestamps) = 0;

protected:
    Window &window;
    vector3df position;
    const std::string name;
    ISceneNodeAnimator *anim;

private:
    const std::string type;
};