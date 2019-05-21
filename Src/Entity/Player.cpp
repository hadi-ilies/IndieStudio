/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Player.cpp
*/

#include "Entity/Player.hpp"

Player::Player(Window &window, const std::string &fileName, const std::string &_name, World &world, const vector3du &pos)
    : Character(window, fileName, world, pos), name(_name), bombType("Timer"), bombPower(3), nbBomb(10)
{
}

Player::~Player()
{
}

bool Player::putBomb()
{
    if (bombList.size() >= nbBomb)
        return false;
    bombList.push_back(unique_ptr<Bomb>(new Bomb(window, bombType, bombPower, world, pos)));
    return true;
}

void Player::aff()
{
    Entity::aff();
    for (unique_ptr<Bomb> &bomb : bombList)
        bomb->aff();
}
