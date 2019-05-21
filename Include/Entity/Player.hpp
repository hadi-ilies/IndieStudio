/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include "Entity/Character.hpp"
#include "Entity/Bomb.hpp"

class Player : public Character
{
public:
    Player(Window &window, const std::string &fileName, const std::string &_name, World &world, const vector3du &pos); // TODO add args (texture ?) or add type var
    ~Player();
    bool putBomb();
    void aff();

private:
    std::string name; // ?
    std::string bombType;
    uint bombPower;
    uint nbBomb;
    std::list<unique_ptr<Bomb>> bombList;
};

#endif
