/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Animation.hpp
*/

#include "Animation.hpp"

Animation::Animation(core::vector3df _cameraPos, core::vector3df _targetPos) : targetPos(_targetPos), speed(4), tightness(0.5), loop(false) {
    camera = nullptr;
    points[0] = _cameraPos;
}

Animation::~Animation() = default;

const array<vector3df> &Animation::getPoints() const {
    return points;
}

const vector3df &Animation::getTargetPos() const {
    return targetPos;
}

float Animation::getSpeed() const {
    return speed;
}

float Animation::getTightness() const {
    return tightness;
}

bool Animation::isLoop() const {
    return loop;
}

scene::ICameraSceneNode *Animation::getCamera() const {
    return camera;
}

void Animation::generatePointsDemo() {
    for (int n = 0 ; n < 64 * 2 ; n += 4) // tmp test
        points.push_back(core::vector3df(cos(n * M_PI / 64) * 20 + 30.5, -5 + n / 4, sin(n * M_PI / 64) * 20 + 30.5));
    points.push_back(core::vector3df(25, 40, 25));
}

void Animation::generatePointsMenu() {

}
