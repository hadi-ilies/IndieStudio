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

class CameraMove
{
public:
    CameraMove();
    CameraMove(const core::vector3df& cameraPos, const core::vector3df& targetPos);
    ~CameraMove();
    const core::array<vector3df> &getPoints() const;
    const vector3df &getTargetPos() const;
    void setTarget(const vector3df &pos);
    void addPoint(const vector3df &menu);
    float getSpeed() const;
    float getTightness() const;
    bool isLoop() const;

private:
    void generatePointsDemo();

private:
    core::array<core::vector3df> points;
    core::vector3df targetPos;
    float speed;
    float tightness;
    bool loop;
};

#endif
