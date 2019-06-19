/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, Zappy group
 * @package 3D FontGenerator
 * @file Irrfont
 */

#ifndef IRRFONT_HPP
#define IRRFONT_HPP

#include <vector>
#include <irrlicht/irrlicht.h>
#include <SFML/Graphics.hpp>

using namespace std;

/**
 * @namespace Irrlicht
 */
using namespace irr;

class IrrFont {
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

#endif /* !IRRFONT_HPP */
