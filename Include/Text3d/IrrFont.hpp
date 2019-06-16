/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IrrFont.hpp
*/

#ifndef IRRFONT_HPP
#define IRRFONT_HPP

#include <vector>
#include <irrlicht/irrlicht.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace irr;

class IrrFont
{
public:
    IrrFont(const sf::Font &font, const char &_c, const uint &size = 100);
    const char &getC() const;
    const float &getAdvance() const;
    const std::vector<core::vector3df> &getPointList() const;
    const std::vector<u16> &getIndiceList() const;
    const scene::E_PRIMITIVE_TYPE &getPrimitiveType() const;

private:
    const char c;
    float advance;
    std::vector<core::vector3df> pointList;
    std::vector<u16> indiceList;
    scene::E_PRIMITIVE_TYPE primitiveType;
};

#endif
