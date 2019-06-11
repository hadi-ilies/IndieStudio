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

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

void client(Player &myPlayer, const sf::IpAddress &ip, const ushort &port);
void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);

int main(int argc, char **argv)
{
    try {
        srand(time(0));
        if (argc == 2 && strncmp(argv[1], "menu", strlen(argv[1])) == 0) {
            std::cout << "i have to call UI class\n"<< std::endl;
            Window &window = Window::getInstance();
            UserInterface userInterface;
            userInterface.create();
            //userInterface.setBackGround("BackgroundMenu.jpg");
            if (userInterface.demo()) {
                userInterface.setBackGround("BackgroundDemo.jpg");
                userInterface.run(vector3df(20, 0, 0), vector3df(10, 0, 0));
            }
        }
        else if (argc == 5 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
            server(std::atoi(argv[2]), argv[3], std::atoi(argv[4]));
        else if (argc == 4 && strncmp(argv[1], "client", strlen(argv[1])) == 0) {
            Player player("Bomberman", "Bob", NULL, vector3du(1, 1, 1));
            client(player, sf::IpAddress(argv[2]), std::atoi(argv[3]));
        }
    }
    catch (Error e) {
        std::cerr << "[" << e.where() << "]" << std::endl;
        std::cerr << "\t" << e.what() << std::endl;
    }
    return 0;
}
