/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Main.cpp
*/

#include <iostream>
#include <cstring> // ?
#include <irrlicht/irrlicht.h>
#include <SFML/Network.hpp> // ?
#include "Window.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"

using namespace std;
using namespace irr;
using namespace sf;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//typedef unsigned short ushort; // TODO move in Type.hpp

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);
void client(const IpAddress &ip, const ushort &port);

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
        world.update();
        player.update();
        window.display(video::SColor(255, 113, 113, 233));
    }
    return true;
}

int main(int argc, char **argv)
{ // TODO try catch
    srand(time(NULL));
    if (argc == 5 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
        server(std::atoi(argv[2]), argv[3], std::atoi(argv[4]));
    else if (argc == 4 && strncmp(argv[1], "client", strlen(argv[1])) == 0)
        client(IpAddress(argv[2]), std::atoi(argv[3]));
    else {
        cerr << "USE : " << argv[0] << " [server]" << endl;
        tmp2(); // tmp
    }
    return 0;
}
