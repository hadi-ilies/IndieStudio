/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Character.hpp
*/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"

#define TIMESTAMP 500

class Character : public Entity
{
public:
    Character(Window *window, const std::string &fileName, World *world, std::string _name, const vector3du &pos);
    virtual ~Character();
    const std::string &getName() const; // ? move in Character
    const uint &getHp() const; // ? move in Character

public:
    bool animHasFinished() const;
    bool checkMove(const vector2di &dir) const;
    bool move(const vector2di &dir);

protected:
    scene::ISceneNodeAnimator *anim;
    std::string name; // ? move in Character
    uint hp; // ? move in Character
};

#endif /* !CHARACTER_HPP */
