/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package UI Package
 * @file UserInterface
 * @remark Core of the UI
 */

#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <arpa/inet.h>
#include <pwd.h>
#include <unistd.h>

#include "Server.hpp"
#include "Client.hpp"
#include "Window.hpp"
#include "Menu.hpp"
#include "World.hpp"
#include "JukeBox.hpp"
#include "Entity/Player.hpp"

#define FONT_TYPE "Resources/Font/Prototype.ttf"
#define GENERATE_FONT "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.<=_%"
#define SOLO 2
#define SERVER_PORT 8080
#define LOCALHOST sf::IpAddress::LocalHost.toString()
#define USERNAME (getpwuid(geteuid()) ? std::string(getpwuid(geteuid())->pw_name) : sf::IpAddress::getLocalAddress().toString())

class UserInterface {
public:
    UserInterface();
    ~UserInterface();
    void setBackGround(const std::string &backGround);

public:
    void create();
    bool demo();
    void run(const vector3df &cameraPos, const vector3df &cameraTarget);

private:
    void ipDisplayer(std::string &ipServer);
    void checkVolume();
    Menu *createMenuBomberman();
    void linkButtonToMenu();
    void createTexture();
    void checkPlayerFeatures();
    void playGame(const std::string &targetIp, const size_t &nbPlayer, const size_t &port, const bool soloMode);
    void changeScene(const vector3df &cameraPos, const vector3df &cameraDestPos, const vector3df &cameraTarget);
    void selectIp(std::string &ipServer);
    bool isIpV4Address(const std::string &ip);
    void createMaps();
    void switchMenu();
    void switchStatusMenu(const std::string &status);

private:
    IrrFontBuffer irrFontBuffer;
    Window window;
    Menu *menu;
    Menu *mainMenu;
    Menu *prevMenu;
    Menu *ipDisplayerMenu;
    Menu *soundMenu;
    Menu *musicMenu;
    scene::ICameraSceneNode *camera;
    float interfaceMusics;
    float interfaceSounds;
    bool lock;
    Player *myPlayer;
    std::string mapGame;

};
