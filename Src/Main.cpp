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

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);
void client(const IpAddress &ip, const ushort &port);

bool tmp2()
{
    Window window("Bomberman", dimension2d<u32>(1920, 1080), false);
    Demo demo;
    //Window window("Bomberman", dimension2d<u32>(1920, 1080), true);
    World world(&window, "Resources/Map/Demo");
    //World world(&window, vector3du(21,2,21));
    Player player(&window, "Bomberman", "Bob", &world, vector3du(1, 1, 1));
    bool spacePress = false; // tmp

    window.runDemo(demo); // tmp

    //world.debugAff();
    window.setDebugMode(true); // tmp
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
        window.display();
    }
    return true;
}

void userInterface(); //tmp

int main(int argc, char **argv)
{
    try {
        srand(time(NULL));
        if (argc == 2 && strncmp(argv[1], "menu", strlen(argv[1])) == 0) {
            std::cout << "i have to call UI class\n"<< std::endl;
            userInterface();
        }
        else if (argc == 5 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
            server(std::atoi(argv[2]), argv[3], std::atoi(argv[4]));
        else if (argc == 4 && strncmp(argv[1], "client", strlen(argv[1])) == 0)
            client(IpAddress(argv[2]), std::atoi(argv[3]));
        else {
            cerr << "USE : " << argv[0] << " [server]" << endl;
            tmp2(); // tmp
        }
    }
    catch (const exception &e) {
        cerr << "ERROR : " << e.what() << endl;
        return 84;
    }
    return 0;
}
