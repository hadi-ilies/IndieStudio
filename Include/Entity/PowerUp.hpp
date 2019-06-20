/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package Entity
 * @file PowerUp
 */


#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <utility>

#include "Entity.hpp"

class PowerUp : public Entity {
public:
    PowerUp(Window *window, std::string _type, World *world, const vector3du &pos);
    ~PowerUp();
    const std::string &getType() const;

private:
    std::string type;
};

#endif /* !POWERUP_HPP */
