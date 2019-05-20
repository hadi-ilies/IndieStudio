/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Main.cpp
*/

#include <iostream>
#include <cstring> // ?
#include <irrlicht/irrlicht.h>
#include "Window.hpp"
#include "World.hpp"
#include "Entity/Character.hpp"

using namespace std;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

bool tmp2()
{
    Window window("Bomberman", dimension2d<u32>(640, 480), false);
    World world(window, "TODO");
    Character player(window, "Resources/Entity/Bomberman", world, vector3du(1, 1, 1));

    //world.debugAff();
    world.aff(); // ? who aff world
    while (window.isOpen()) {
        // TODO
        if (window.isKeyPressed(KEY_KEY_Q))
            player.move(vector2di(-1, 0));
        else if (window.isKeyPressed(KEY_KEY_D))
            player.move(vector2di(1, 0));
        else if (window.isKeyPressed(KEY_KEY_Z))
            player.move(vector2di(0, 1));
        else if (window.isKeyPressed(KEY_KEY_S))
            player.move(vector2di(0, -1));
        player.aff(); // ? who aff entity
        window.display(video::SColor(255,113,113,133));
    }
    return true;
}

int main(int argc, char **argv)
{ // TODO try catch
    srand(time(NULL));
    if (argc == 2 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
        cout << "server" << endl;
    else if (argc == 1)
        cout << "client" << endl;
    else
        cerr << "USE : " << argv[0] << " [server]" << endl;
    tmp2(); // tmp
    return 0;
}
