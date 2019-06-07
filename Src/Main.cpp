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
#include <JukeBox.hpp>
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

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);
void client(const sf::IpAddress &ip, const ushort &port);

bool Demo()
{
    Window window("Bomberman", dimension2d<u32>(1920, 1080), false);
    window.changeSkybox("Resources/Texture/demo.jpg");
    CameraMove cameraMoove;
    World world(&window, "Resources/Map/DemoWithoutEdge");
    JukeBox jukeBox;
    Player player(&window, "Bomberman", "Bob", &world, vector3du(1, 1, 1));
    bool spacePress = false; // tmp
    window.applyCameraMove(cameraMoove); // tmp

    //world.debugAff();
    window.setDebugMode(true); // tmp
    jukeBox.addSound("test", "Resources/Sounds/Menu.ogg");
    jukeBox.playSound("test");
    while (window.isOpen()) {
        world.update();
        player.update();
        window.display(); //move player
    }
    return true;
}
//todo put demo + userinterface in a class
bool demo(Window *window);
void userInterface(Window *window); //tmp

int main(int argc, char **argv)
{
    try {
        srand(time(NULL));
        if (argc == 2 && strncmp(argv[1], "menu", strlen(argv[1])) == 0) {
            std::cout << "i have to call UI class\n"<< std::endl;
            Window window("Bomberman", dimension2d<u32>(1920, 1080), false);
            if (demo(&window));
                userInterface(&window);
        }
        else if (argc == 5 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
            server(std::atoi(argv[2]), argv[3], std::atoi(argv[4]));
        else if (argc == 4 && strncmp(argv[1], "client", strlen(argv[1])) == 0)
            client(sf::IpAddress(argv[2]), std::atoi(argv[3]));
        else {
            cerr << "USE : " << argv[0] << " [server]" << endl;
            Demo(); // tmp
        }
    }
    catch (const exception &e) {
        cerr << "ERROR : " << e.what() << endl;
        return 84;
    }
    return 0;
}
