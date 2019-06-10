/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CameraMove.hpp
*/

#ifndef BOMBERMAN_DEMO_HPP
#define BOMBERMAN_DEMO_HPP

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;

class CameraMove {
public:
    CameraMove();
    CameraMove(const core::vector3df &_cameraPos, const core::vector3df &_targetPos, const float &_speed = 4); // ?
    ~CameraMove();
    const core::array<vector3df> &getPoints() const;
    const vector3df &getTargetPos() const;
    const float &getSpeed() const;
    const float &getTightness() const;
    const bool &getLoop() const;
    void setTarget(const vector3df &pos);
    void setSpeed(const float &_speed);
    void setLoop(bool loop);

public:
    void addPoint(const vector3df &point);

public:
    void generateFirstMove();
    void generateDemoSecondMove();

private:
    core::array<core::vector3df> pointsList;
    core::vector3df targetPos;
    float speed;
    float tightness;
    bool loop;
};

#endif /* !BOMBERMAN_DEMO_HPP */
