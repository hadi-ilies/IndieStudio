/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** PowerUp.hpp
*/

#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <utility>

#include "Entity.hpp"

class PowerUp : public Entity
{
public:
    PowerUp(std::string _type, World *world, const vector3du &pos);
    ~PowerUp();
    const std::string &getType() const;

private:
    std::string type;
};

#endif
