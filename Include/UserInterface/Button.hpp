/*
** EPITECH PROJECT, 2019
** button
** File description:
** button
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include "Entity.hpp"
#include "Window.hpp"

using namespace irr;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

typedef vector3d<uint> vector3du; //tmp

class Button {
public:
	Button(Window *window, vector3df &position); //maybe add type of button
	~Button();
        ISceneNode *getButton() const;
        vector3df getPosition() const;
        bool animHasFinished() const;
        bool animation(Window *window, const vector3df &destPos, const f32 &timestamps);
private:
        //const string type;
        ISceneNodeAnimator *anim;
        vector3df position;
        ISceneNode *button;
};
