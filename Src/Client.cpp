/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Client.cpp
*/

#include <iostream> // ?
#include <thread>
#include <vector>
#include "Window.hpp"
#include "Error.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp" //?
#include "FormattedSocket.hpp"

using namespace std;
using namespace irr;
using namespace sf;

bool startTurn = false; // tmp no global
bool endTurn = false; // tmp no global

enum PlayerAction {None, Up, Down, Left, Right, PutBomb};

void serverLoop(FormattedSocket *client)
{
    while (client->receive()) {
        if (client->type != StartTurn)
            throw Error("Thread failed 1");
        startTurn = true;
        while (startTurn && client->isConnected());
    }
    if (client->isConnected())
        throw Error("Thread failed");
}

static bool turnHasFinished(vector<unique_ptr<Player>> &playerList)
{
    bool check = true;

    for (unique_ptr<Player> &player: playerList)
        if (!player->animHasFinished())
            check = false;
    return check;
}

static bool getKey(const Window &window, PlayerAction &key)
{
    if (window.isKeyPressed(KEY_SPACE))
        key = PutBomb;
    else if (window.isKeyPressed(KEY_KEY_Q) || window.isKeyPressed(KEY_KEY_A))
        key = Left;
    else if (window.isKeyPressed(KEY_KEY_D) || window.isKeyPressed(KEY_KEY_E))
        key = Right;
    else if (window.isKeyPressed(KEY_KEY_Z) || window.isKeyPressed(KEY_KEY_W))
        key = Up;
    else if (window.isKeyPressed(KEY_KEY_S))
        key = Down;
    else
        return false;
    return true;
}

static void execPlayerAction(PlayerAction &key, FormattedSocket &client, World &world, vector<unique_ptr<Player>> &playerList)
{
    if (key == PutBomb) {
        if (!client.sendPlayerPutBomb())
            throw Error("SendPlayerBomb");
    }
    else if (key == Left) {
        if (!client.sendPlayerMove(vector2di(-1, 0)))
            throw Error("SendPlayer(-1, 0)");
    }
    else if (key == Right) {
        if (!client.sendPlayerMove(vector2di(1, 0)))
            throw Error("SendPlayer(1, 0)");
    }
    else if (key == Up) {
        if (!client.sendPlayerMove(vector2di(0, 1)))
            throw Error("SendPlayer(0, 1)");
    }
    else if (key == Down) {
        if (!client.sendPlayerMove(vector2di(0, -1)))
            throw Error("SendPlayer(0, -1)");
    }
    else if (!client.sendPlayerMove(vector2di(0, 0)))
        throw Error("sendPlayerMove(0, 0)");
    for (unique_ptr<Player> &player: playerList) {
        if (!client.receive())
            throw Error("client Receiver");
        if (client.type == PlayerMove)
            player->move(client.direction);
        else if (client.type == PlayerPutBomb)
            if (!player->putBomb())
                player->move(vector2di(0, 0));
        player->update();
    }
    world.update();
    startTurn = false;
    endTurn = true;
    key = None;
}

//NOTE : playerId not used there but it will be usefull

static void game(Window &window, FormattedSocket &client, World &world, vector<unique_ptr<Player>> &playerList, const size_t &playerId)
{
    thread loop(serverLoop, &client);
    PlayerAction key = None;

    while (window.isOpen() && client.isConnected()) {
        if (window.isKeyPressed(KEY_ESCAPE))
            window.close();
        getKey(window, key);
        if (startTurn)
            execPlayerAction(key, client, world, playerList);
        if (endTurn)
            if (turnHasFinished(playerList)) {
                if (!client.sendEndTurn())
                    throw Error("sendEndTurn failed");
                endTurn = false;
                //key = None; control Corentin dont remove it
            }
        window.display(video::SColor(255, 113, 113, 233));
    }
    client.disconnect();
    startTurn = true; // for exit thread
    loop.join();
}

void client(const IpAddress &ip, const ushort &port) //put player in param
{
    FormattedSocket client;
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    //World myWorld(&window, "TODO"); // Todo put pointer on world constructor. this we allow us to put NULL in constructor
    Player myPlayer(NULL, "Bomberman", "Bob", NULL, vector3du(1, 1 ,1));
    myPlayer.changeTexture("Default");
    if (!client.connect(ip, port))
        throw Error("an error has been detected in Connect function");
    size_t nbPlayer;

    std::cout << "FileName : " << myPlayer.getFileName() << std::endl;
    std::cout << "Model : " << myPlayer.getModel() << std::endl;
    std::cout << "Texture : " << myPlayer.getTexture() << std::endl;
    std::cout << "Name : " << myPlayer.getName() << std::endl;
    client.sendMessage(myPlayer.getFileName());
    client.sendMessage(myPlayer.getTexture());
    client.sendMessage(myPlayer.getName());

    if (!client.receive())
        throw Error("receive error 1");
    if (client.type != Message)
        throw Error("message error");
    cout << client.message << endl;
    World world(&window, client.message);
    vector<unique_ptr<Player>> playerList;

    if (!client.receive())
        throw Error("receive error 2");
    //nb powerup
    if (!client.receive())
        throw Error("receive error bonus");
    if (client.type != Number)
        throw Error("uint 32 Error");
    size_t nbPowerUp = client.number;
    //loop type position
    vector<unique_ptr<PowerUp>> powerUpList;
    for (size_t i = 0; i < nbPowerUp; i++) {
        //type
        if (!client.receive())
            throw Error("message Error");
        if (!client.type != Message)
            throw Error("type error");
        std::string powerUpType = client.message;
        //position
        if (!client.receive())
            throw Error("message Error");
        if (!client.type != Position)
            throw Error("Position error");
        vector3du powerUpPosition = client.position;
        powerUpList.push_back(unique_ptr<PowerUp>(new PowerUp(&window, powerUpType, &world, powerUpPosition)));
    }
    if (client.type != Number)
        throw Error("uint 32 error");
    nbPlayer = client.number;

    for (size_t i = 0; i < nbPlayer; i++) {
        if (!client.receive())
            throw Error("receive error 3");
        if (client.type != Message)
            throw Error("model error");
        std::string fileName = client.message;

        if (!client.receive())
            throw Error("receive error 4");
        if (client.type != Message)
            throw Error("Texture error");
        std::string texture = client.message;

        if (!client.receive())
            throw Error("receive error 5");
        if (client.type != Message)
            throw Error("name error");
        std::string name = client.message;

        if (!client.receive())
            throw Error("receive error 6");
        if (client.type != Position)
            throw Error("Position error");
        vector3du position = client.position;

        playerList.push_back(unique_ptr<Player>(new Player(&window, fileName, name, &world, position)));
        playerList.back()->changeTexture(texture);
    }
    if (!client.receive())
        throw Error("receive error 7");
    if (client.type != Number)
        throw Error("uint 32 error id");
    size_t playerId = client.number;

    cout << "ZIZI" << endl;
    game(window, client, world, playerList, playerId);
}
