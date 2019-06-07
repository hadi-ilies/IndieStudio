/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CameraMove.hpp
*/

#include "CameraMove.hpp"

CameraMove::CameraMove()
        : targetPos(vector3df(25, 0.5, 25)), speed(4), tightness(0.5), loop(false)
{
    generatePointsDemo();
}

CameraMove::CameraMove(const core::vector3df &_cameraPos, const core::vector3df &_targetPos, const float &_speed)
    : targetPos(_targetPos), speed(_speed), tightness(0.5), loop(false)
{
    points.push_back(_cameraPos);
}

CameraMove::~CameraMove()
{
}

const array<vector3df> &CameraMove::getPoints() const
{
    return points;
}

const vector3df &CameraMove::getTargetPos() const
{
    return targetPos;
}

const float &CameraMove::getSpeed() const
{
    return speed;
}

const float &CameraMove::getTightness() const
{
    return tightness;
}

const bool &CameraMove::getLoop() const
{
    return loop;
}

void CameraMove::setTarget(const vector3df &pos)
{
    targetPos = pos;
}

void CameraMove::setSpeed(const float &_speed)
{
    speed = _speed;
}

void CameraMove::addPoint(const vector3df &menu)
{
    points.push_back(menu);
}

void CameraMove::generatePointsDemo()
{
    for (int n = 0 ; n < 64 * 2 ; n += 4) // tmp test
        points.push_back(core::vector3df(cos(n * M_PI / 64) * 20 + 30.5, -5 + n / 4, sin(n * M_PI / 64) * 20 + 30.5));
    points.push_back(core::vector3df(25, 40, 25));
}
