/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(const std::string &_name, const vector3du &pos); // TODO add args (texture ?)
    ~Player();

private:
    std::string name;
};

#endif
