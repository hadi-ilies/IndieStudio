/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Demo.hpp
*/

#include "Demo.hpp"

/*
 *   Constructors // Destructors
 */
Demo::Demo() {
    lookAt = vector3df(25, 0.5, 25);
    speed = 4;
    tightness = 0.5;
    loop = false;

    generatePoints();
}

Demo::~Demo() = default;
/*
 *   Getters // Setters
 */
const array<vector3df> &Demo::getPoints() const {
    return points;
}

const vector3df &Demo::getLookAt() const {
    return lookAt;
}

float Demo::getSpeed() const {
    return speed;
}

float Demo::getTightness() const {
    return tightness;
}

bool Demo::isLoop() const {
    return loop;
}

/*
 *   Methods
 */
void Demo::generatePoints() {
    for (int n = 0; n < 64 * 2; n += 4) // tmp test
        points.push_back(core::vector3df(cos(n * M_PI / 64) * 20 + 30.5, -5 + n / 4, sin(n * M_PI / 64) * 20 + 30.5));
    points.push_back(core::vector3df(25, 40, 25));
}