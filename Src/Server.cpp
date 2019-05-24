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
    std::list<unique_ptr<FormattedSocket>> socketList;

    cerr << "start server" << endl;
    if (listener.listen(port) != Socket::Done)
        throw Error("listen failed");
    for (size_t i = 0; i < nbPlayer; i++) {
        unique_ptr<FormattedSocket> socket = unique_ptr<FormattedSocket>(new FormattedSocket);

        if (!socket->accept(listener))
            throw Error("accept failed");
        cerr << "new client" << endl;
        socketList.push_back(move(socket));
    }
    listener.close();
    cerr << "clients connected" << endl;

    /*// init
    for (unique_ptr<FormattedSocket> &socket : socketList) {
        socket->sendMessage(worldFileName); // tmp TODO send World
        socket->sendUint32(socketList.size());
        /*for (unique_ptr<FormattedSocket> &socket : socketList) {
            socket->sendMessage("Resources/Entity/Bomberman"); // tmp TODO send player
            // TODO
        }
    }*/


    // loop
    while (!socketList.empty()) {
        for (unique_ptr<FormattedSocket> &socket : socketList)
            if (!socket->sendStartTurn())
                throw Error("send failed");
        for (unique_ptr<FormattedSocket> &socket : socketList)
            if (!socket->receive())
                throw Error("receiver failed");
        for (unique_ptr<FormattedSocket> &socket : socketList) {
            /*if (socket->type == PlayerMove) {
              socket->sendPlayerMove(socket->dir); // tmp
              }
              else if (socket->type == PlayerPutBomb) {
              socket->sendPlayerPutBomb(); // tmp
              }
              else
              throw Error("bad type");*/
            for (unique_ptr<FormattedSocket> &socket2 : socketList)
                //if (socket != socket2) {
                if (socket2->type == PlayerMove) {
                    socket->sendPlayerMove(socket2->dir); // tmp
                }
                else if (socket2->type == PlayerPutBomb) {
                    socket->sendPlayerPutBomb(); // tmp
                }
                else
                    throw Error("bad type");
        }
    }
    // TODO
}
cerr << "stop server" << endl;
}
