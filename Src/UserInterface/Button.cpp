/*
** EPITECH PROJECT, 2019
** Button
** File description:
** Button
*/

#include "Error.hpp"
#include "UserInterface/Button.hpp"

Button::Button(Window *window, const vector3df &position, const std::string &name, const std::string &model, const std::string &texture)
    : position (position), model(model), texture(texture), anim(NULL), name(name)
{
    if (window) {
        button = window->addAnimatedMesh((std::string) "Resources/Entity/" + model + "/Model/Idle.md2", (std::string) "Resources/Entity/" + model + "/Texture/" + texture + ".png");
        if (!button)
            throw Error("button can not be created");
        button->setPosition(position);
    }
}

Button::~Button()
{
}

const std::string Button::getName() const
{
    return name;
}

const std::string Button::getTexture() const
{
    return texture;
}

const std::string Button::getModel() const
{
    return model;
}


vector3df Button::getPosition() const
{
    return position;
}

#include <iostream> //tmp
bool Button::animHasFinished() const
{
    return !anim || anim->hasFinished();
}

bool Button::animation(Window *window, const vector3df &destPos, const f32 &timestamps)
{
    if (!animHasFinished())
        return false;
    anim = window->createTranslation(position, destPos, timestamps);
    position = destPos;
    if (anim) {
        button->addAnimator(anim);
        anim->drop();
    }
    return true;
}
