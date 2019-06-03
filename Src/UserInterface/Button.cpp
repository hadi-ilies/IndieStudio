/*
** EPITECH PROJECT, 2019
** Button
** File description:
** Button
*/

#include "Error.hpp"
#include "UserInterface/Button.hpp"

Button::Button(Window *window, vector3du &position)
    : position (position), button(window ? window->addCube("Resources/Block/Wall/Texture.png") : NULL) //may i have to add types
{
    if (window) {
        const vector3df floatPosition(position.X, position.Y, position.Z);

        if (!button)
            throw Error("button can not be created");
        button->setPosition(floatPosition);
    }
}

Button::~Button()
{
}

vector3du Button::getPositon() const
{
    return position;
}

#include <iostream>
scene::ISceneNodeAnimator *Button::animation(Window *window, const vector3df &pos, const float &timeStamp)
{
    scene::ISceneNodeAnimator* anim = window->createCircleAnimation(pos, timeStamp);
    vector3df cameraPos(5, 0, -15);
    vector3df target(0, 0, 20);
    scene::ICameraSceneNode* camera = window->getCameraSceneNode(cameraPos, target);

    if (anim) {
        std::cout << "ZIZI" << std::endl;
		button->addAnimator(anim);
		anim->drop();
	}
    return anim;
}
