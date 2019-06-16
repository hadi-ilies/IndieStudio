/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Window.hpp
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <irrlicht/irrlicht.h>
#include "EventReceiver.hpp"
#include "CameraMove.hpp"
#include "Error.hpp"

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
    const bool &getDebugMode() const;
    void setDebugMode(const bool &active);
    void close();
    bool isOpen();
    void display();
    IAnimatedMesh *getModel(const std::string &fileName);
    ITexture *getTexture(const std::string &fileName);
    ISceneNode *addCube(const std::string &texture); // ? ISceneNode or IMeshSceneNode
    IAnimatedMeshSceneNode *addAnimatedMesh(const std::string &model, const std::string &texture);
    ISceneNodeAnimator *createTranslation(const vector3df &initPos, const vector3df &destPos, const u32 &timestamp);
    ICameraSceneNode *getCameraSceneNode(const vector3df &pointOfView, const vector3df &lookAt); // ?
    bool isKeyPressed(const irr::EKEY_CODE &keyCode) const;
    void changeSkybox(const std::string &fileName);
    ISceneNodeAnimator *applyCameraMove(const CameraMove &cameraMoove);
    void canBeResized(bool isResize);
    ISceneManager *getSmgr(); // TODO supr // ? use friend

private:
    void debugMode();

private:
    EventReceiver receiver;
    IrrlichtDevice *device;
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
    bool debug;
};

#endif /* !WINDOW_HPP */
