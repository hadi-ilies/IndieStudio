/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Animation.hpp
*/

#include "CameraMoove.hpp"

CameraMoove::CameraMoove()
        : targetPos(vector3df(25, 0.5, 25)), speed(4), tightness(0.5), loop(false)
{
    generatePointsDemo();
}

CameraMoove::CameraMoove(const core::vector3df& _cameraPos, const core::vector3df& _targetPos) : targetPos(_targetPos), speed(4), tightness(0.5), loop(false) {
    points[0] = _cameraPos;
}

CameraMoove::~CameraMoove() = default;

const array<vector3df> &CameraMoove::getPoints() const {
    return points;
}

const vector3df &CameraMoove::getTargetPos() const {
    return targetPos;
}

float CameraMoove::getSpeed() const {
    return speed;
}

float CameraMoove::getTightness() const {
    return tightness;
}

bool CameraMoove::isLoop() const {
    return loop;
}

void CameraMoove::generatePointsDemo() {
    for (int n = 0 ; n < 64 * 2 ; n += 4) // tmp test
        points.push_back(core::vector3df(cos(n * M_PI / 64) * 20 + 30.5, -5 + n / 4, sin(n * M_PI / 64) * 20 + 30.5));
    points.push_back(core::vector3df(25, 40, 25));
}

void CameraMoove::generatePointsMenu() {

}
