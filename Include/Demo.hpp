/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Demo.hpp
*/

#ifndef BOMBERMAN_DEMO_HPP
#define BOMBERMAN_DEMO_HPP

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;

class Demo {
public:
    Demo();
    ~Demo();
    const core::array<vector3df> &getPoints() const;
    const vector3df &getLookAt() const;
    float getSpeed() const;
    float getTightness() const;
    bool isLoop() const;

private:
    void generatePoints();

private:
    core::array<core::vector3df> points;
    core::vector3df lookAt;
    float speed;
    float tightness;
    bool loop;
};


#endif /* !BOMBERMAN_DEMO_HPP */
