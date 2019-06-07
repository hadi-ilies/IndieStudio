/*
** EPITECH PROJECT, 2019
** Button
** File description:
** Button
*/

#include "Error.hpp"
#include "UserInterface/Button.hpp"

Button::Button(Window *window, const vector3df &position, const std::string &name, IAnimatedMeshSceneNode *mesh)
    : position (position), button(mesh), anim(NULL), name(name)
{
    if (window) {
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
