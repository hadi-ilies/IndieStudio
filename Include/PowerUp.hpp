/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** PowerUp.hpp
*/

#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <string>
#include "Entity.hpp"

class PowerUp : public Entity
{
public:
    PowerUp(const std::string &_type, const vector3du &pos); // TODO add args (texture ?)
    ~PowerUp();

private:
    std::string type;
};

#endif
