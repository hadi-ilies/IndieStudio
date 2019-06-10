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

void client(Player &myPlayer, const sf::IpAddress &ip, const ushort &port);
void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);

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
/*
 * void WindowMove::runDemo() {
    Window &window = Window::getInstance();
    JukeBox &jukeBox = JukeBox::getInstance();
    World world("Resources/Map/DemoWithoutEdge");

    window.changeSkybox("Resources/Texture/demo.jpg");
    CameraMove cameraMove1;
    CameraMove cameraMove2;

    cameraMove1.generateDemoFirstMove();
    cameraMove2.generateDemoSecondMove();
    cameraMove2.setLoop(true);

    window.applyCameraMove(cameraMove1); // tmp
    window.applyCameraMove(cameraMove2);

    jukeBox.addMusic("DemoMusic", "Resources/Sound_Effects/Musics/DemoMusic.ogg");
    jukeBox.playMusic("DemoMusic");
}

void WindowMove::runUI() {
    // TODO
}
 */
bool Demo()
{
    Window &window = Window::getInstance();
    window.changeSkybox("Resources/Texture/demo.jpg");
    CameraMove cameraMoove;
    World world("Resources/Map/DemoWithoutEdge");
    JukeBox &jukeBox = JukeBox::getInstance();
    Player player("Bomberman", "Bob", &world, vector3du(1, 1, 1));
    bool spacePress = false; // tmp
    cameraMoove.generateFirstMove();
    window.applyCameraMove(cameraMoove);


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
            UserInterface userInterface;
            userInterface.create();
            userInterface.setBackGround("demo.jpg");
            if (userInterface.demo()) {
                userInterface.setBackGround("background.png");
                userInterface.run(vector3df(20, 0, 0), vector3df(10, 0, 0));
            }
        }
        else if (argc == 5 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
            server(std::atoi(argv[2]), argv[3], std::atoi(argv[4]));
        else if (argc == 4 && strncmp(argv[1], "client", strlen(argv[1])) == 0) {
            Player player("Bomberman", "Bob", NULL, vector3du(1, 1, 1));
            client(player, sf::IpAddress(argv[2]), std::atoi(argv[3]));
        }
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
