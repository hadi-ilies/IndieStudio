/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(const std::string &_name, World &world, const Vector3u &pos)
    : Entity(world, pos), name(_name), bombType("Timer"), bombPower(3), nbBomb(1)
{
}

Player::~Player()
{
}

bool Player::putBomb()
{
    if (bombList >= nbBomb)
        return false;
    bombList.push_back(unique_ptr<Bomb> Bomb(bombType, bombPower, world, pos));
    return true;
}
