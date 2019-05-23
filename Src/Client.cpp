/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Client.cpp
*/

#include <iostream> // ?
#include "Window.hpp"
#include "Error.hpp"
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

void client(const IpAddress &ip, const ushort &port)
{
    cerr << ip << "  " << port << endl;
    //Window window("Bomberman", dimension2d<u32>(1920, 1080), true);
    TcpSocket client;


    if (client.connect(ip, port) != Socket::Done)
        throw Error("an Error has been detected in Connect function");
    Packet packet;
    int type;
    client.receive(packet);

    packet >> type;
    cout << type << endl;
    if (type == Message) {
        std::string msg;
        packet >> msg;
        cout <<  msg << endl;
    }
    //structure enum type data
    // union
}
