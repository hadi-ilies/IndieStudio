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
Character::Character(Window *window, const std::string &fileName, World *world, const std::string &_name,
                     const vector3du &position) : Entity(window, fileName, world, position), name(_name),
                                                  anim(nullptr), hp(1) {
    if (window)
        JukeBox::getInstance().addSound("Damage", "Resources/Sound/Damage.ogg");
}

Character::~Character() = default;

/*
 * Getters // Setters
 */
const std::string &Character::getName() const {
    return name;
}

const uint &Character::getHp() const {
    return hp;
}

/*
 * Methods
 */
/**
 * Check the status of the current animation
 * @return Animation status
 */
bool Character::animHasFinished() const {
    return !anim || anim->hasFinished();
}

bool Character::takeDamage() {
    if (hp) {
        hp--;
        if (window)
            JukeBox::getInstance().playSound("Damage");
        if (!hp)
            if (mesh)
                //mesh->setVisible(false); // ??
                mesh->setRotation(vector3df(0, 0, 90));
    }
    return !hp;
}

/**
 * Check if the character move is possible
 * @param dir
 * @return True if the move is possible, false otherwise
 */
bool Character::checkMove(const vector2di &dir) const {
    const vector3du newPosition(position.X + dir.X, position.Y,
                                position.Z + dir.Y);

    if (newPosition.X >= world->getSize().X || newPosition.Y >= world->getSize().Y
        || newPosition.Z >= world->getSize().Z)
        return false;
    return !(world->getBlock(newPosition) && world->getBlock(newPosition)->getOpaque());
}

/**
 * Move the character
 * @param dir
 * @return True if success, false otherwise
 */
bool Character::move(const vector2di &dir) {
    vector2di newDir = dir;

    if (!animHasFinished())
        return false;
    if (!checkMove(dir))
        newDir = vector2di(0, 0);

    const vector3du newPosition(position.X + newDir.X, position.Y,
                                position.Z + newDir.Y); // vct2.Y is the vec3.Z
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
