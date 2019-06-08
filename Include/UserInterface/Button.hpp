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
#include "UserInterface/AButton.hpp"

class Button : public AButton {
public:
	Button(Window *window, const vector3df &position, const std::string &name, const std::string &model, const std::string &texture);
        //Button(Window *window, const vector3df &position, const std::string &name, IAnimatedMesh *button);
	~Button();
        const std::string getTexture() const;
        const std::string getModel() const;
        bool animation(Window *window, const vector3df &destPos, const f32 &timestamps);
private:
        const std::string model;
        const std::string texture;
        //ISceneNode *button;
        IAnimatedMeshSceneNode *button;
        //wordSceneNote remove model and texture
};
