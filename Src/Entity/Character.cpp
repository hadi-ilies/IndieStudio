/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Character.cpp
*/

#include "Entity/Character.hpp"

/*
 * Constructors // Destructors
 */
Character::Character(Window *window, const std::string &fileName, World *world, std::string _name, const vector3du &position)
    : Entity(window, fileName, world, position),
      name(std::move(_name)), anim(nullptr), hp(1)
{
}

Character::~Character() = default;
/*
 * Getters // Setters
 */

/*
 * Methods
 */
const std::string &Character::getName() const
{
    return name;
}

const uint &Character::getHp() const
{
    return hp;
}

bool Character::animHasFinished() const {
    return !anim || anim->hasFinished();
}

bool Character::checkMove(const vector2di &dir) const {
    const vector3du newPosition(position.X + dir.X, position.Y, position.Z + dir.Y); // vct2.Y is the vec3.Z

    if (newPosition.X >= world->getSize().X || newPosition.Y >= world->getSize().Y
        || newPosition.Z >= world->getSize().Z)
        return false;
    return !(world->getBlock(newPosition) && world->getBlock(newPosition)->getOpaque());
}

bool Character::move(const vector2di &dir) {
    vector2di newDir = dir;

    if (!animHasFinished())
        return false;
    if (!checkMove(dir))
        newDir = vector2di(0, 0);

    const vector3du newPosition(position.X + newDir.X, position.Y, position.Z + newDir.Y); // vct2.Y is the vec3.Z
    const vector3df initPosition(position.X, position.Y, position.Z);
    const vector3df destPosition(newPosition.X, newPosition.Y, newPosition.Z);

    if (mesh)
        if ((anim = window->createTranslation(initPosition, destPosition, TIMESTAMP)))
            mesh->addAnimator(anim);
    if (newDir.X == 0 && newDir.Y == 0)
        changeModel("Idle");
    else {
        changeModel("Walk");

        // take direction
        if (mesh) {
            irr::core::vector3df rotation;

            if (newDir.X == -1 && newDir.Y == 0)
                rotation.Y = 0;
            else if (newDir.X == 1 && newDir.Y == 0)
                rotation.Y = 180;
            else if (newDir.X == 0 && newDir.Y == -1)
                rotation.Y = -90;
            else if (newDir.X == 0 && newDir.Y == 1)
                rotation.Y = 90;
            mesh->setRotation(rotation);
        }
        position = newPosition;
    }
    return true;
}
