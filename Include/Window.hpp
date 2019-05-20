/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Window.hpp
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <irrlicht/irrlicht.h>
#include "EventReceiver.hpp"

using namespace std;
using namespace irr;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Window
{
public:
    Window(const std::string &windowName, dimension2d<u32> size, const bool &fullscreen);
    ~Window();
    bool isOpen();
    void display(const SColor &color);
    ISceneNode *addCube(const std::string &texture); // ? ISceneNode or IMeshSceneNode
    IAnimatedMeshSceneNode *addAnimatedMesh(const std::string &model, const std::string &texture);
    bool isKeyPressed(const irr::EKEY_CODE &keyCode) const;

private:
    EventReceiver receiver;
    IrrlichtDevice *device;
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
};

#endif
