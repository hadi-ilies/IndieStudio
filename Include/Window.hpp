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
#include "CameraMove.hpp"
#include "Text3d/WordSceneNode.hpp"
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
    static Window &getInstance();
    const bool &getDebugMode() const;
    void setDebugMode(const bool &active);
    void close();
    bool isOpen();
    void display();
    IAnimatedMesh *getModel(const std::string &fileName);
    ITexture *getTexture(const std::string &fileName);
    ISceneNode *addCube(const std::string &texture); // ? ISceneNode or IMeshSceneNode
    IAnimatedMeshSceneNode *addAnimatedMesh(const std::string &model, const std::string &texture);
    WordSceneNode *addText(const std::string &str);
    ISceneNodeAnimator *createTranslation(const vector3df &initPos, const vector3df &destPos, const u32 &timestamp);
    ICameraSceneNode *getCameraSceneNode(const vector3df &pointOfView, const vector3df &lookAt); // ?
    bool isKeyPressed(const irr::EKEY_CODE &keyCode) const;
    void changeSkybox(const std::string &fileName);
    ISceneNodeAnimator *applyCameraMove(const CameraMove &cameraMoove);

private:
    /*Window& operator=(const Window&){}
    Window(const Window&){}*/
    Window(const std::string &windowName, dimension2d<u32> size, const bool &fullscreen);
    ~Window();
    void debugMode();

private:
    static Window windowInstance; // ? // TODO rename instance // TODO use unique_ptr
    IrrFontBuffer irrFontBuffer;
    EventReceiver receiver;
    IrrlichtDevice *device;
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
    bool debug;
};

#endif
