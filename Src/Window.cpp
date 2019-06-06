/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Window.cpp
*/

#include "Window.hpp"

Window::Window(const std::string &windowName, dimension2d<u32> size, const bool &fullscreen)
    : debug(false)
{
    const wstring title(windowName.begin(), windowName.end());

    device = createDevice(video::EDT_OPENGL, size, 16, fullscreen, false, false, &receiver);
    if (!device)
        throw Error("device cant bo create");
    device->setWindowCaption(title.c_str());
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNodeFPS(0, 100, 0.05); // tmp
    device->getCursorControl()->setVisible(false); // tmp

    //device->getCursorControl()->setVisible(false); // tmp
}

Window::~Window()
{
    close();
    device->drop();
}

const bool &Window::getDebugMode() const
{
    return debug;
}

void Window::setDebugMode(const bool &active)
{
    debug = active;
}

void Window::close()
{
    device->closeDevice();
}

bool Window::isOpen()
{
    return device->run();
}

void Window::display()
{
    if (debug)
        debugMode();
    driver->beginScene();
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
}

IAnimatedMesh *Window::getModel(const std::string &fileName)
{
    return smgr->getMesh(fileName.c_str());
}

ITexture *Window::getTexture(const std::string &fileName)
{
    return driver->getTexture(fileName.c_str());
}

ISceneNode *Window::addCube(const std::string &texture)
{
    scene::ISceneNode *node = smgr->addCubeSceneNode(1);

    if (!node)
        return NULL;
    node->setMaterialTexture(0, driver->getTexture(texture.c_str())); // ? throw if getTexture failed
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    return node;
}

IAnimatedMeshSceneNode *Window::addAnimatedMesh(const std::string &model, const std::string &texture)
{
    IAnimatedMesh *mesh = smgr->getMesh(model.c_str());
    IAnimatedMeshSceneNode *node;

    if (!mesh)
        return NULL;
    node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture(texture.c_str()));
    }
    return node;
}

ISceneNodeAnimator *Window::createTranslation(const vector3df &initPos, const vector3df &destPos, const u32 &timestamp)
{
    return smgr->createFlyStraightAnimator(initPos, destPos, timestamp);
}

ICameraSceneNode *Window::getCameraSceneNode(const vector3df &pointOfView, const vector3df &lookAt)
{
    return smgr->addCameraSceneNode(0, pointOfView, lookAt);
}

bool Window::isKeyPressed(const irr::EKEY_CODE &keyCode) const
{
    return receiver.IsKeyDown(keyCode);
}

void Window::changeSkybox(const std::string &fileName)
{
    smgr->addSkyDomeSceneNode(getTexture(fileName));
}

void Window::applyCameraMove(const CameraMove &cameraMoove)
{
    scene::ICameraSceneNode *camera = nullptr;
    scene::ISceneNodeAnimator *sa = nullptr;

    camera = getCameraSceneNode(cameraMoove.getPoints()[0], cameraMoove.getTargetPos());
    sa = smgr->createFollowSplineAnimator(device->getTimer()->getTime(), cameraMoove.getPoints(), cameraMoove.getSpeed(), cameraMoove.getTightness(), cameraMoove.isLoop());
    camera->addAnimator(sa);
    sa->drop();
}

void Window::debugMode()
{
    wchar_t text[255];
    IGUISkin *skin;

    guienv->clear();
    swprintf(text, 255, L"fps: %3d", driver->getFPS()); // ?
    skin = guienv->getSkin();
    skin->setColor(gui::EGDC_BUTTON_TEXT, video::SColor(255, 255, 255, 0));
    guienv->addStaticText(text, rect<s32>(10, 10, 55, 22), true);
}

// TODO supr func
/*void Window::demoAnimation(core::array<core::vector3df> points, const core::vector3df& lookAt) {
    scene::ICameraSceneNode* camera = nullptr;
    scene::ISceneNodeAnimator* sa = nullptr;

    camera = getCameraSceneNode(points[0], lookAt);
    sa = smgr->createFollowSplineAnimator(this->getDevice()->getTimer()->getTime(), points, 4, 0.5, false);
    camera->addAnimator(sa);
    sa->drop();
}
*/
