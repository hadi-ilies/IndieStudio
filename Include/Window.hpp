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
    void close();
    bool isOpen();
    IVideoDriver *getDriver() const;
    IGUIEnvironment *getGuienv() const;
    void display(const SColor &color);
    IAnimatedMesh *getModel(const std::string &fileName);
    ITexture *getTexture(const std::string &fileName);
    ISceneNode *addCube(const std::string &texture); // ? ISceneNode or IMeshSceneNode
    IAnimatedMeshSceneNode *addAnimatedMesh(const std::string &model, const std::string &texture);
    ISceneNodeAnimator *createTranslation(const vector3df &initPos, const vector3df &destPos, const u32 &timestamp);
    bool isKeyPressed(const irr::EKEY_CODE &keyCode) const;
    void displayFPS();
private:
    EventReceiver receiver;
    IrrlichtDevice *device;
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
    s32 lastfps;
};

#endif