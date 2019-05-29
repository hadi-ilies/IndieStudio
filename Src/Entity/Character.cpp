/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Character.cpp
*/

#include "Entity/Character.hpp"

Character::Character(Window *window, const std::string &fileName, World *world, const vector3du &position)
    : Entity(window, fileName, world, position), anim(NULL)
{
}

Character::~Character()
{
}

bool Character::animHasFinished() const
{
    return !anim || anim->hasFinished();
}

bool Character::checkMove(const vector2di &dir) const
{
    vector3du newPosition(position.X + dir.X, position.Y, position.Z + dir.Y); // vct2.Y is the vec3.Z

    if (newPosition.X >= world->getSize().X || newPosition.Y >= world->getSize().Y || newPosition.Z >= world->getSize().Z)
        return false;
    if (world->getBlock(newPosition) && world->getBlock(newPosition)->getOpaque())
        return false;
    return true;
}

bool Character::move(const vector2di &dir)
{
    vector3du newPosition(position.X + dir.X, position.Y, position.Z + dir.Y); // vct2.Y is the vec3.Z

    if (!animHasFinished())
        return false;
    if (!checkMove(dir))
        newPosition = position;

    const vector3df initPosition(position.X, position.Y, position.Z);
    const vector3df destPosition(newPosition.X, newPosition.Y, newPosition.Z);

    if (anim = window->createTranslation(initPosition, destPosition, TIMESTAMP))
        mesh->addAnimator(anim);
    if (dir.X == 0 && dir.Y == 0)
        changeModel("Idle");
    else {
        changeModel("Walk");

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
        position = newPosition;
    }
    return true;
}
