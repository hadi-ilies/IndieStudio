/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @file Utility
 * @brief Globpp like (use boost library)
 */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <vector>
#include <string>
#include <irrlicht/irrlicht.h>
#include <boost/filesystem.hpp>

using namespace std;

/**
 * @namespace Irrlicht
 */
using namespace irr;
using namespace core;

/**
 * @brief vectory alias
 */
typedef vector2d<uint> vector2du;
typedef vector3d<uint> vector3du;

vector<std::string> globpp(const std::string &pathFolder);

#endif /* !UTILITY_HPP */
