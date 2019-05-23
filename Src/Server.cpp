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
#include "FormattedSocket.hpp"

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

#include <unistd.h> // tmp
void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer)
{
    TcpListener listener;
    //std::list<FormattedSocket> socketList;
    FormattedSocket socket;

    if (listener.listen(port) != Socket::Done)
        throw Error("listen failed");
    cerr << "listen start" << endl;
    /*for (size_t i = 0; i < nbPlayer; i++) {
      TcpSocket socket;*/

        if (listener.accept(socket.socket) != Socket::Done)
            throw Error("accept failed");
        //socketList.push_back(socket);
        //}
    listener.close();
    cerr << "client connected" << endl;

    while (true) {
        usleep(500000); // tmp
        if (!socket.sendStartTurn())
            throw Error("send failed");
        if (!socket.receive())
            throw Error("receiver failed");
        if (socket.type == PlayerMove) {
            socket.sendPlayerMove(socket.dir); // tmp
        }
        else if (socket.type == PlayerPutBomb) {
            socket.sendPlayerPutBomb(); // tmp
        }
        else
            throw Error("bad type");
        // TODO
    }
}
