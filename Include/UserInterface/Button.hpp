/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
 * @package UI Package
 * @file Button
 */

#pragma once

#include <irrlicht/irrlicht.h>
#include <utility>

#include "Entity.hpp"
#include "Window.hpp"
#include "UserInterface/ButtonElement.hpp"
#include "UserInterface/AButton.hpp"

class Button : public AButton {
public:
    Button(Window &window, const vector3df &position, const std::string &name, const std::string &model, const std::string &texture);
    ~Button();
    const std::string getTexture() const;
    const std::string getModel() const;

public:
    bool animation(const vector3df &destPos, const f32 &timestamps) override;

private:
    const std::string model;
    const std::string texture;
    IAnimatedMeshSceneNode *button;
};
