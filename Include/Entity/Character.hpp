/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Character.hpp
*/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"

class Character : public Entity
{
public:
    Character(Window &window, const std::string &fileName, World &world, const vector3du &pos);
    ~Character();
    bool animHasFinished() const;
    //bool checkMove(const vector2di &dir); // ?
    bool move(const vector2di &dir);

private:
    scene::ISceneNodeAnimator *anim;
};

#endif
