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
#include "Entity/Player.hpp"

using namespace std;
using namespace irr;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

void server(const std::string &worldFileName, const size_t &nbPlayer);
void client();

bool tmp2()
{
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    //Window window("Bomberman", dimension2d<u32>(1920, 1080), true);
    World world(window, "TODO");
    Player player(window, "Resources/Entity/Bomberman", "Bob", world, vector3du(1, 1, 1));
    bool spacePress = false; // tmp

    //world.debugAff();
    while (window.isOpen()) {
        // TODO
        if (window.isKeyPressed(KEY_ESCAPE))
            window.close();
        else if (window.isKeyPressed(KEY_KEY_Q) || window.isKeyPressed(KEY_KEY_A))
            player.move(vector2di(-1, 0));
        else if (window.isKeyPressed(KEY_KEY_D))
            player.move(vector2di(1, 0));
        else if (window.isKeyPressed(KEY_KEY_Z) || window.isKeyPressed(KEY_KEY_W))
            player.move(vector2di(0, 1));
        else if (window.isKeyPressed(KEY_KEY_S))
            player.move(vector2di(0, -1));
        else if (window.isKeyPressed(KEY_SPACE)) {
            if (!spacePress)
                player.putBomb();
            spacePress = true;
        }
        else {
            player.move(vector2di(0, 0));
            spacePress = false;
        }
        player.update();
        world.aff(); // ? who aff world
        player.aff(); // ? who aff entity
        window.display(video::SColor(255, 113, 113, 233));
    }
    return true;
}

int main(int argc, char **argv)
{ // TODO try catch
    srand(time(NULL));
    if (argc == 2 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
        server("TODO", 2);
    else if (argc == 1)
        client();
    else
        cerr << "USE : " << argv[0] << " [server]" << endl;
    tmp2(); // tmp
    return 0;
}
