/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Animation.hpp
*/

#include "CameraMove.hpp"

CameraMove::CameraMove()
        : targetPos(vector3df(25, 0.5, 25)), speed(4), tightness(0.5), loop(false)
{
    generatePointsDemo();
}

CameraMove::CameraMove(const core::vector3df& _cameraPos, const core::vector3df& _targetPos)
    : targetPos(_targetPos), speed(4), tightness(0.5), loop(false)
{
    points.push_back(_cameraPos);
}

CameraMove::~CameraMove() = default;

const array<vector3df> &CameraMove::getPoints() const {
    return points;
}

const vector3df &CameraMove::getTargetPos() const {
    return targetPos;
}

float CameraMove::getSpeed() const {
    return speed;
}

float CameraMove::getTightness() const {
    return tightness;
}

bool CameraMove::isLoop() const {
    return loop;
}

void CameraMove::generatePointsDemo() {
    for (int n = 0 ; n < 64 * 2 ; n += 4) // tmp test
        points.push_back(core::vector3df(cos(n * M_PI / 64) * 20 + 30.5, -5 + n / 4, sin(n * M_PI / 64) * 20 + 30.5));
    points.push_back(core::vector3df(25, 40, 25));
}

void CameraMove::addPoint(const vector3df &menu)
{
    //if (points.size() > 0) {
    //    for (int n = points.back())
   // }
    points.push_back(menu);
}
