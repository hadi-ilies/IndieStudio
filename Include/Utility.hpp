/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Utility.hpp
*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <vector>
#include <string>
#include <irrlicht/irrlicht.h>
#include <boost/filesystem.hpp>

using namespace std;
using namespace irr;
using namespace core;

typedef vector2d<uint> vector2du;
typedef vector3d<uint> vector3du;

vector<std::string> globpp(const std::string &pathFolder);

#endif /* !UTILITY_HPP */
