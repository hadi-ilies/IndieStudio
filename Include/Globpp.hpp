/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Globpp.hpp
*/

#ifndef GLOBPP_HPP
#define GLOBPP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <glob.h>
#include "Error.hpp"

using namespace std;

vector<std::string> globpp(const std::string &pattern) // TODO move in cpp
{
    vector<std::string> pathList;
    glob_t pglob;

    if (glob(pattern.c_str(), GLOB_MARK, NULL, &pglob))
        throw Error("glob error");
    for (size_t i = 0; i < pglob.gl_pathc; i++)
        pathList.push_back(std::string(pglob.gl_pathv[i]));
    globfree(&pglob);
    return pathList;
}

#endif
