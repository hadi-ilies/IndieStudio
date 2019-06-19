/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CameraMove.hpp
*/

#include "CameraMove.hpp"

/*
 * Constructors // Destructors
 */
/**
 * Default constructor
 */
CameraMove::CameraMove() : targetPos(vector3df(25, 0.5, 25)), speed(4), tightness(0.5), loop(false) {

}

/**
 * Constructor used when vectors are already initialize
 * @param _cameraPos
 * @param _targetPos
 * @param _speed
 */
CameraMove::CameraMove(const core::vector3df &_cameraPos, const core::vector3df &_targetPos,
                       const float &_speed) : targetPos(_targetPos), speed(_speed), tightness(0.5),
                                              loop(false) {
    pointsList.push_back(_cameraPos);
}

CameraMove::~CameraMove() = default;

/*
 * Getters // Setters
 */
const array <vector3df> &CameraMove::getPoints() const {
    return pointsList;
}

const vector3df &CameraMove::getTargetPos() const {
    return targetPos;
}

const float &CameraMove::getSpeed() const {
    return speed;
}

const float &CameraMove::getTightness() const {
    return tightness;
}

const bool &CameraMove::getLoop() const {
    return loop;
}

void CameraMove::setTarget(const vector3df &pos) {
    targetPos = pos;
}

void CameraMove::setSpeed(const float &_speed) {
    speed = _speed;
}

void CameraMove::setLoop(bool _loop) {
    CameraMove::loop = _loop;
}

/*
 * Methods
 */
void CameraMove::addPoint(const vector3df &menu) {
    pointsList.push_back(menu);
}

void CameraMove::generateFirstMove() {
    for (int n = 0 ; n < 64 * 2 ; n += 4)
        pointsList.push_back(core::vector3df(cos(n * M_PI / 64) * 20 + 30.5, -5 + n / 4,
                                             sin(n * M_PI / 64) * 20 + 30.5));
    pointsList.push_back(core::vector3df(25, 40, 25));
}

void CameraMove::generateDemoSecondMove() {
    /*for (int i = 15 ; i <= 35 ; i++)
        pointsList.push_back(core::vector3df(10,40,i));
    for (int i = 35 ; i >= 15 ; i--)
        pointsList.push_back(core::vector3df(10,40,i));*/
    for (int i = 0 ; i <= 50 ; i++)
        pointsList.push_back(core::vector3df(10, 20, i));
    for (int i = 50 ; i >= 0 ; i--)
        pointsList.push_back(core::vector3df(10, 20, i));
}