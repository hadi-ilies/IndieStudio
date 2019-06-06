/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Animation.hpp
*/

#ifndef BOMBERMAN_DEMO_HPP
#define BOMBERMAN_DEMO_HPP

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;

class Animation
{
public:
    Animation(core::vector3df cameraPos, core::vector3df targetPos);
    ~Animation();
    const core::array<vector3df> &getPoints() const;
    const vector3df &getTargetPos() const;
    float getSpeed() const;
    float getTightness() const;
    bool isLoop() const;
    scene::ICameraSceneNode *getCamera() const;

private:
    void generatePointsDemo();
    void generatePointsMenu();

private:
    scene::ICameraSceneNode *camera;
    core::array<core::vector3df> points;
    core::vector3df targetPos;
    float speed;
    float tightness;
    bool loop;
};

#endif
