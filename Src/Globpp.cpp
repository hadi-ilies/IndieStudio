/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Globpp.cpp
*/

#include "Globpp.hpp"

vector<std::string> globpp(const std::string &pattern)
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
