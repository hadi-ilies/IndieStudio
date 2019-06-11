#include <memory>

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

bool startTurn = false; // tmp no global
bool endTurn = false; // tmp no global

enum PlayerAction {None, Up, Down, Left, Right, PutBomb};

void serverLoop(FormattedSocket *client)
{
    while (client->receive()) {
        if (client->type != StartTurn)
            throw Error("Thread failed", __FILE__, __FUNCTION__, __LINE__);
        startTurn = true;
        while (startTurn && client->isConnected());
    }
    if (client->isConnected())
        throw Error("Thread failed", __FILE__, __FUNCTION__, __LINE__);
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

static void execPlayerAction(PlayerAction &key, FormattedSocket &client, World &world, vector<unique_ptr<PowerUp>> &powerUpList, vector<unique_ptr<Player>> &playerList, const size_t &playerId)
{
    if (playerList[playerId]->getHp()) {
        if (key == PutBomb) {
            if (!client.sendPlayerPutBomb())
                throw Error("SendPlayerBomb error", __FILE__, __FUNCTION__, __LINE__);
        }
        else if (key == Left) {
            if (!client.sendPlayerMove(vector2di(-1, 0)))
                throw Error("SendPlayer(-1, 0)", __FILE__, __FUNCTION__, __LINE__);
        }
        else if (key == Right) {
            if (!client.sendPlayerMove(vector2di(1, 0)))
                throw Error("SendPlayerMov(1, 0)", __FILE__, __FUNCTION__, __LINE__);
        }
        else if (key == Up) {
            if (!client.sendPlayerMove(vector2di(0, 1)))
                throw Error("SendPlayerMove(0, 1)", __FILE__, __FUNCTION__, __LINE__);
        }
        else if (key == Down) {
            if (!client.sendPlayerMove(vector2di(0, -1)))
                throw Error("SendPlayerMove(0, -1)", __FILE__, __FUNCTION__, __LINE__);
        }
        else if (!client.sendPlayerMove(vector2di(0, 0)))
            throw Error("SendPlayerMove(0, 0)", __FILE__, __FUNCTION__, __LINE__);
    }
    else if (!client.sendPlayerMove(vector2di(0, 0)))
        throw Error("SendPlayerMove(0, 0)", __FILE__, __FUNCTION__, __LINE__);
    for (unique_ptr<Player> &player: playerList) {
        if (!client.receive())
            throw Error("Client receiver", __FILE__, __FUNCTION__, __LINE__);
        if (client.type == PlayerMove)
            player->move(client.direction);
        //check colision enenmies
        if (world.getBlock(player->getPosition()) && world.getBlock(player->getPosition())->getType() == "Fire")
            player->takeDamage();
        //check colision power up
        for (auto it = powerUpList.begin(); it != powerUpList.end();) {
            if (world.getBlock((*it)->getPosition()) && world.getBlock((*it)->getPosition())->getType() == "Fire")
                it = powerUpList.erase(it);
            else if (player->getPosition() == (*it)->getPosition()) {
                player->takePowerUp(**it);
                it = powerUpList.erase(it);
            }
            else
                it++;
        }
        if (client.type == PlayerPutBomb) //else if
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

static void game(Window &window, FormattedSocket &client, World &world, vector<unique_ptr<PowerUp>> &powerUpList, vector<unique_ptr<Player>> &playerList, const size_t &playerId)
{
    thread loop(serverLoop, &client);
    PlayerAction key = None;

    while (window.isOpen() && client.isConnected()) {
        if (window.isKeyPressed(KEY_ESCAPE))
            window.close();
        getKey(window, key);
        if (startTurn)
            execPlayerAction(key, client, world, powerUpList, playerList, playerId);
        if (endTurn)
            if (turnHasFinished(playerList)) {
                if (!client.sendEndTurn())
                    throw Error("SendEndTurn failed", __FILE__, __FUNCTION__, __LINE__);
                endTurn = false;
                //key = None; control Corentin dont remove it
            }
        window.display();
    }
    client.disconnect();
    startTurn = true; // for exit thread
    loop.join();
}

void client(Player &myPlayer, const sf::IpAddress &ip, const ushort &port) //put player in param
{
    FormattedSocket client;
    Window &window = Window::getInstance();
    //World myWorld("TODO"); // Todo put pointer on world constructor. this we allow us to put NULL in constructor
    //Player myPlayer("Bomberman", "Bob", NULL, vector3du(1, 1 ,1));
    //myPlayer.changeTexture("Default");
    if (!client.connect(ip, port))
        throw Error("An error has been detected in Connect function", __FILE__, __FUNCTION__, __LINE__);
    size_t nbPlayer;

    std::cout << "FileName : " << myPlayer.getFileName() << std::endl;
    std::cout << "Model : " << myPlayer.getModel() << std::endl;
    std::cout << "Texture : " << myPlayer.getTexture() << std::endl;
    std::cout << "Name : " << myPlayer.getName() << std::endl;
    client.sendMessage(myPlayer.getFileName());
    client.sendMessage(myPlayer.getTexture());
    client.sendMessage(myPlayer.getName());

    if (!client.receive())
        throw Error("Receive error", __FILE__, __FUNCTION__, __LINE__);
    if (client.type != Message)
        throw Error("Message error", __FILE__, __FUNCTION__, __LINE__);
    cout << client.message << endl;
    World world("Resources/Map/" + client.message);
    vector<unique_ptr<Player>> playerList;

    //nb powerup
    if (!client.receive())
        throw Error("Receive bonus error", __FILE__, __FUNCTION__, __LINE__);
    if (client.type != Number)
        throw Error("uin32 error", __FILE__, __FUNCTION__, __LINE__);
    size_t nbPowerUp = client.number;
    //loop type position
    vector<unique_ptr<PowerUp>> powerUpList;
    cout << "nb power up : " << nbPowerUp << endl;
    for (size_t i = 0; i < nbPowerUp; i++) {
        //type
        if (!client.receive())
            throw Error("Message error", __FILE__, __FUNCTION__, __LINE__);
        if (client.type != Message)
            throw Error("Type error", __FILE__, __FUNCTION__, __LINE__);
        std::string powerUpType = client.message;
        //position
        if (!client.receive())
            throw Error("Message error", __FILE__, __FUNCTION__, __LINE__);
        if (client.type != Position)
            throw Error("Position error", __FILE__, __FUNCTION__, __LINE__);
        vector3du powerUpPosition = client.position;
        powerUpList.push_back(std::make_unique<PowerUp>(powerUpType, &world, powerUpPosition));
        powerUpList.back()->update();
    }
    if (!client.receive())
        throw Error("Receive error", __FILE__, __FUNCTION__, __LINE__);
    if (client.type != Number)
        throw Error("uin32 error", __FILE__, __FUNCTION__, __LINE__);
    nbPlayer = client.number;

    for (size_t i = 0; i < nbPlayer; i++) {
        if (!client.receive())
            throw Error("Receive error", __FILE__, __FUNCTION__, __LINE__);
        if (client.type != Message)
            throw Error("Model error", __FILE__, __FUNCTION__, __LINE__);;
        std::string fileName = client.message;

        if (!client.receive())
            throw Error("Receive error", __FILE__, __FUNCTION__, __LINE__);
        if (client.type != Message)
            throw Error("Texture error", __FILE__, __FUNCTION__, __LINE__);;
        std::string texture = client.message;

        if (!client.receive())
            throw Error("Receive error", __FILE__, __FUNCTION__, __LINE__);
        if (client.type != Message)
            throw Error("Name error", __FILE__, __FUNCTION__, __LINE__);
        std::string name = client.message;

        if (!client.receive())
            throw Error("Receive error", __FILE__, __FUNCTION__, __LINE__);
        if (client.type != Position)
            throw Error("Position error", __FILE__, __FUNCTION__, __LINE__);
        vector3du position = client.position;

        playerList.push_back(std::make_unique<Player>(fileName, name, &world, position));
        playerList.back()->changeTexture(texture);
    }
    if (!client.receive())
        throw Error("Receive error", __FILE__, __FUNCTION__, __LINE__);
    if (client.type != Number)
        throw Error("uint32 error", __FILE__, __FUNCTION__, __LINE__);
    size_t playerId = client.number;

    game(window, client, world, powerUpList, playerList, playerId);
}
