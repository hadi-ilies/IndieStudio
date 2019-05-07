/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(const std::string &_name, const vector3du &pos)
    : Entity(pos), name(_name)
{
}

Player::~Player()
{
}
