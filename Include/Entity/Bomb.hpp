/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Bomb.hpp
*/

#ifndef BOMB_HPP
#define BOMB_HPP

#include "Entity.hpp"

class Bomb : public Entity {
public:
    Bomb(const std::string &_type, const uint &_power, World *world, const vector3du &pos);
    ~Bomb();
    const std::string &getType() const;
    const uint &getPower() const;
    //const uint &getTick() const; // ? TODO

public:
    void update() override;
    void detonate(); // ? const

private:
    std::string type; // ?
    uint power;
    uint tick; // ? TODO
};

#endif /* !BOMB_HPP */
