/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AButton
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

typedef vector3d<uint> vector3du; //tmp

class AButton {
	public:
		AButton(Window *window, const vector3df &position, const std::string &name, const std::string &type);
		~AButton();
        const std::string getName() const;
        vector3df getPosition() const;
        bool animHasFinished() const;
        virtual bool animation(Window *window, const vector3df &destPos, const f32 &timestamps) = 0;
	protected:
        Window *window;
        vector3df position;
        const std::string name;
        ISceneNodeAnimator *anim;
    private:
        const std::string type;
};