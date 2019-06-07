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
	Button(Window *window, const vector3df &position, const std::string &name, const std::string &model, const std::string &texture);
        //Button(Window *window, const vector3df &position, const std::string &name, IAnimatedMesh *button);
	~Button();
        const std::string getName() const;
        const std::string getTexture() const;
        const std::string getModel() const;
        vector3df getPosition() const;
        bool animHasFinished() const;
        bool animation(Window *window, const vector3df &destPos, const f32 &timestamps);
private:
        const std::string name;
        const std::string model;
        const std::string texture;
        ISceneNodeAnimator *anim;
        vector3df position;
        //ISceneNode *button;
        IAnimatedMeshSceneNode *button;
};
