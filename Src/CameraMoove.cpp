/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Animation.hpp
*/

#include "CameraAnimation.hpp"

CameraAnimation::CameraAnimation()
        : targetPos(vector3df(25, 0.5, 25)), speed(4), tightness(0.5), loop(false)
{
    generatePointsDemo();
}

CameraAnimation::CameraAnimation(core::vector3df _cameraPos, core::vector3df _targetPos) : targetPos(_targetPos), speed(4), tightness(0.5), loop(false) {
    camera = nullptr;
    points[0] = _cameraPos;
}

CameraAnimation::~CameraAnimation() = default;

const array<vector3df> &CameraAnimation::getPoints() const {
    return points;
}

const vector3df &CameraAnimation::getTargetPos() const {
    return targetPos;
}

float CameraAnimation::getSpeed() const {
    return speed;
}

float CameraAnimation::getTightness() const {
    return tightness;
}

bool CameraAnimation::isLoop() const {
    return loop;
}

scene::ICameraSceneNode *CameraAnimation::getCamera() const {
    return camera;
}

void CameraAnimation::generatePointsDemo() {
    for (int n = 0 ; n < 64 * 2 ; n += 4) // tmp test
        points.push_back(core::vector3df(cos(n * M_PI / 64) * 20 + 30.5, -5 + n / 4, sin(n * M_PI / 64) * 20 + 30.5));
    points.push_back(core::vector3df(25, 40, 25));
}

void CameraAnimation::generatePointsMenu() {

}
