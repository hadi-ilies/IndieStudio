/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Client.cpp
*/

#include <iostream> // ?
#include "Window.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Sender.hpp"

using namespace std;
using namespace irr;
using namespace sf;

static void game(Window &window)
{
    //World world(window, worldFileName); // TODO create with socket
}

void client(char *ip, int port)
{
    //cerr << ip << "  " << port << endl;
    Window window("Bomberman", dimension2d<u32>(1920, 1080), true);
    IpAddress ipAddr(ip);
    TcpSocket client;
    client.connect(ipAddr, port);
    exit(0);
    //structure enum type data
    // union
}
