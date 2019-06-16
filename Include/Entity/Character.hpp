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

class Character : public Entity {
public:
    Character(Window *window, const std::string &fileName, World *world, const vector3du &pos);
    virtual ~Character();

public:
    bool animHasFinished() const;
    bool checkMove(const vector2di &dir) const;
    bool move(const vector2di &dir);

protected:
    scene::ISceneNodeAnimator *anim;
};

#endif /* !CHARACTER_HPP */
