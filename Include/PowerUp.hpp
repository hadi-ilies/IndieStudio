/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** PowerUp.hpp
*/

#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "Entity.hpp"

class PowerUp : public Entity
{
public:
    PowerUp(const string &_type, World &world, const vector3du &pos);
    ~PowerUp();

private:
    string type;
};

#endif
