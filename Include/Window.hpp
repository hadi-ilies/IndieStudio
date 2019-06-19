/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, Zappy group
 * @file World (Map, Map generator)
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <irrlicht/irrlicht.h>

#include "EventReceiver.hpp"
#include "CameraMove.hpp"
#include "Error.hpp"

using namespace std;

/**
 * @namespace Irrlicht
 */
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Window {
public:
    Window(const std::string &windowName, dimension2d<u32> size, const bool &fullscreen);
    ~Window();
    const bool &getDebugMode() const;
    void setDebugMode(const bool &active);
    ISceneManager *getSmgr();

public:
    void close();
    bool isOpen();
    void display();
    IAnimatedMesh *getModel(const std::string &fileName);
    ITexture *getTexture(const std::string &fileName);
    ISceneNode *addCube(const std::string &texture);
    IAnimatedMeshSceneNode *addAnimatedMesh(const std::string &model, const std::string &texture);
    ISceneNodeAnimator *createTranslation(const vector3df &initPos, const vector3df &destPos, const u32 &timestamp);
    ICameraSceneNode *getCameraSceneNode(const vector3df &pointOfView, const vector3df &lookAt);
    bool isKeyPressed(const irr::EKEY_CODE &keyCode) const;
    void changeSkybox(const std::string &fileName);
    ISceneNodeAnimator *applyCameraMove(const CameraMove &cameraMoove);
    void canBeResized(bool isResize);

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
