/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Utility.cpp
*/

#include "Utility.hpp"

vector<string> globpp(const std::string &pathFolder)
{
    boost::filesystem::path p (pathFolder);
    boost::filesystem::directory_iterator end_itr;
    vector<string> filesList;

    for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr)
    {
        if (is_regular_file(itr->path())) {
            filesList.push_back(itr->path().string());
        }
    }
    return filesList;
}
