/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, Zappy group
 * @package Entity
 * @file Character
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"

#define TIMESTAMP 500

class Character : public Entity {
public:
    Character(Window *window, const std::string &fileName, World *world, const std::string &_name, const vector3du &pos);
    virtual ~Character();
    const std::string &getName() const;
    const uint &getHp() const;

public:
    bool animHasFinished() const;
    bool takeDamage();
    bool checkMove(const vector2di &dir) const;
    bool move(const vector2di &dir);

protected:
    scene::ISceneNodeAnimator *anim;
    std::string name;
    uint hp;
};

#endif /* !CHARACTER_HPP */
