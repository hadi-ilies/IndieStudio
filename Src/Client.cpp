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
#include "Receiver.hpp"

using namespace std;
using namespace irr;
using namespace sf;

static void game(Window &window, Receiver &receiver, Sender &sender)
{
    //World world(window, worldFileName); // TODO create with socket
    //Window window("Bomberman", dimension2d<u32>(1920, 1080), true);
    World world(window, "TODO");
    Player player(window, "Resources/Entity/Bomberman", "Bob", world, vector3du(1, 1, 1));

    while (window.isOpen()) {
        if (receiver.receive()) {
            if (receiver.type == Message) {
                cout << "RECEIVED :" << receiver.message << endl;
            }

            //tmp2
            if (window.isKeyPressed(KEY_ESCAPE))
                window.close();
            else if (window.isKeyPressed(KEY_KEY_Q) || window.isKeyPressed(KEY_KEY_A))
                sender.sendPlayerMove(vector2di(-1, 0));
            else if (window.isKeyPressed(KEY_KEY_D))
                sender.sendPlayerMove(vector2di(1, 0));
            else if (window.isKeyPressed(KEY_KEY_Z) || window.isKeyPressed(KEY_KEY_W))
                sender.sendPlayerMove(vector2di(0, 1));
            else if (window.isKeyPressed(KEY_KEY_S))
                sender.sendPlayerMove(vector2di(0, -1));
            else if (window.isKeyPressed(KEY_SPACE))
                sender.sendPlayerPutBomb();
            else
                sender.sendPlayerMove(vector2di(0, 0));
            world.update();
            player.update();
            window.display(video::SColor(255, 113, 113, 233));
            }
    }
}

void client(const IpAddress &ip, const ushort &port)
{
    TcpSocket client;
    if (client.connect(ip, port) != Socket::Done)
        throw Error("an Error has been detected in Connect function");
    Receiver receiver(client);
    Sender sender(client);
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    game(window, receiver, sender);
    //structure enum type data
    // union
}
