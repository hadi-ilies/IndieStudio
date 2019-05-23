/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Server.cpp
*/

#include <iostream> // ?
#include <list>
#include "Window.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Error.hpp"
#include "Sender.hpp"
#include "Receiver.hpp"

using namespace std;
using namespace irr;
using namespace sf;

/*void server(const std::string &worldFileName, const size_t &nbPlayer)
{
    Window window("Bomberman", dimension2d<u32>(800, 600), false);
    World world(window, worldFileName);
    //std::list<Player> playerList;
    std::list<TcpSocket> socketList;

    TcpListener listener;

    if (listener.listen(53000) != sf::Socket::Done)
        throw Error("listen failed");

    for (size_t i = 0; i < nbPlayer; i++) {
        TcpSocket socket;

        cerr << "wait player" << i + 1 << endl;
        if (listener.accept(socket) != sf::Socket::Done)
            throw Error("accept failed");
            }


    while (window.isOpen()) {
        // TODO
        }
}*/

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer)
{
    TcpListener listener;
    TcpSocket socket;

    if (listener.listen(port) != Socket::Done)
        throw Error("listen failed");
    cerr << "listen start" << endl;
    if (listener.accept(socket) != Socket::Done)
        throw Error("accept failed");
    listener.close();
    cerr << "client connected" << endl;
    Sender sender(socket);
    Receiver receiver(socket);

    while (true) {
        if (sender.sendStartTurn())
            throw Error("send failed");
        if (!receiver.receive())
            throw Error("send failed");
        if (receiver.type != Message)
            throw Error("bad type");
        //receiver // TODO
        if (sender.sendMessage("My"))
            throw Error("send failed");
    }

}
