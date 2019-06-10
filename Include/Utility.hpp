/*
** EPITECH PROJECT, 2019
** Bomberman
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

typedef vector3d<uint> vector3du;

vector<std::string> globpp(const std::string &pathFolder);

#endif /* !UTILITY_HPP */
