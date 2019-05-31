/*
** EPITECH PROJECT, 2019
** button
** File description:
** button
*/

#pragma once

#include <irrlicht/irrlicht.h>
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
		Button(Window *window, vector3du &position); //maybe add type of button
		~Button();
        ISceneNode *getButton() const;
        vector3du getPositon() const;
	private:
        //const string type;
        vector3du position;
        ISceneNode *button;
};
