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

vector<std::string> globpp(const std::string &pathFolder) {
    boost::filesystem::path p(pathFolder);
    boost::filesystem::directory_iterator end_itr;
    vector<std::string> filesList;

    for (boost::filesystem::directory_iterator it(p) ; it != end_itr ; it++)
        if (is_regular_file(it->path()))
            filesList.push_back(it->path().string());
    return filesList;
}

#endif /* !UTILITY_HPP */
