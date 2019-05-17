/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include "Character.hpp"
#include "Bomb.hpp"

class Player : public Character
{
public:
    Player(const string &_name, World &world, const vector3du &pos); // TODO add args (texture ?) or add type var
    ~Player();
    bool putBomb();

private:
    string name; // ?
    string bombType;
    uint bombPower;
    uint nbBomb;
    list<unique_ptr<Bomb>> bombList;
};

#endif
