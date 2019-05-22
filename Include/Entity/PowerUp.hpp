/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** PowerUp.hpp
*/

#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "Entity.hpp"

class PowerUp : public Entity
{
public:
    PowerUp(Window &window, const std::string &_type, World &world, const vector3du &pos);
    ~PowerUp();

private:
    std::string type;
};

#endif
