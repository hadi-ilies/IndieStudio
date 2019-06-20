/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Utility.cpp
*/

#include "Utility.hpp"

vector<std::string> globpp(const std::string &pathFolder) {
    boost::filesystem::path p(pathFolder);
    boost::filesystem::directory_iterator end_itr;
    vector<std::string> filesList;

    for (boost::filesystem::directory_iterator it(p) ; it != end_itr ; it++)
        if (is_regular_file(it->path()))
            filesList.push_back(it->path().string());
    return filesList;
}
