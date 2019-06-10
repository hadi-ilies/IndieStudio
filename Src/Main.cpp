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
#include "UserInterface/UserInterface.hpp"

using namespace std;
using namespace irr;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);
void client(const sf::IpAddress &ip, const ushort &port);

/*
 *  WindowMove windowMove;
    Window &window = Window::getInstance();
    World world("Resources/Map/DemoWithoutEdge");

    windowMove.runDemo();

    while (window.isOpen()) {
        window.display(); //move player
    }
    return true;
 */
bool Demo()
{
    Window &window = Window::getInstance();
    window.changeSkybox("Resources/Texture/demo.jpg");
    CameraMove cameraMoove;
    World world(&window, "Resources/Map/DemoWithoutEdge");
    JukeBox &jukeBox = JukeBox::getInstance();
    Player player(&window, "Bomberman", "Bob", &world, vector3du(1, 1, 1));
    bool spacePress = false; // tmp
    window.applyCameraMove(cameraMoove); // tmp

    //world.debugAff();
    window.setDebugMode(true); // tmp
    jukeBox.addMusic("test", "Resources/Sound_Effects/Musics/DemoMusic.ogg");
    jukeBox.playMusic("test");
    while (window.isOpen()) {
        world.update();
        player.update();
        window.display(); //move player
    }
    return true;
}
//todo put demo + userinterface in a class

int main(int argc, char **argv)
{
    try {
        srand(time(NULL));
        if (argc == 2 && strncmp(argv[1], "menu", strlen(argv[1])) == 0) {
            std::cout << "i have to call UI class\n"<< std::endl;
            Window &window = Window::getInstance();
            UserInterface userInterface(&window);
            userInterface.create();
            userInterface.setBackGround("demo.jpg");
            if (userInterface.demo()) {
                userInterface.setBackGround("background.png");
                userInterface.run(vector3df(20, 0, 0), vector3df(10, 0, 0));
            }
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
