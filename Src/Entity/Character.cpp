/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Character.cpp
*/

#include "Entity/Character.hpp"

Character::Character(Window &window, const std::string &fileName, World &world, const vector3du &pos)
    : Entity(window, fileName, world, pos), anim(NULL)
{
}

Character::~Character()
{
}

bool Character::move(const vector2di &dir)
{
    vector3du newPos(pos.X + dir.X, pos.Y, pos.Z + dir.Y); // vct2.Y is the vec3.Z

    if (newPos.X >= world.getSize().X || newPos.Y >= world.getSize().Y || newPos.Z >= world.getSize().Z)
        return false;
    if (world.getBlock(newPos) && world.getBlock(newPos)->getOpaque())
        return false;

    const vector3df initPos (pos.X, pos.Y, pos.Z);
    const vector3df destPos (newPos.X, newPos.Y, newPos.Z);
    const u32 timestamp = 500;

    if (dir.Y == 0 && dir.X == 0)
        changeModel("Idle");
    else if (!anim || anim->hasFinished()) {
        changeModel("Walk");
        anim = window.createTranslation(initPos, destPos, timestamp);
        if (anim) {
            mesh->addAnimator(anim);
        }
        pos = newPos;

        // take direction
        irr::core::vector3df rotation;

        if (dir.X == -1 && dir.Y == 0)
            rotation.Y = 0;
        else if (dir.X == 1 && dir.Y == 0)
            rotation.Y = 180;
        else if (dir.X == 0 && dir.Y == -1)
            rotation.Y = -90;
        else if (dir.X == 0 && dir.Y == 1)
            rotation.Y = 90;
        mesh->setRotation(rotation);
    }
    return true;
}
