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

static void game(Window &window)
{
    //World world(window, worldFileName); // TODO create with socket
}

void client(char *ip, int port)
{
    Window window("Bomberman", dimension2d<u32>(1920, 1080), true);
    IpAddress::IpAddress ipAddr(ip);
    TcpSocket client();
    client.connect(ipAddr, port, seconds(1));
    //structure enum type data
    // union
}
