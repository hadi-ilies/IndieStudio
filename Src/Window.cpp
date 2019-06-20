/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Window.cpp
*/

#include "Window.hpp"

/**
 * Window constructor
 * @param windowName
 * @param size
 * @param is fullscreen
 */
Window::Window(const std::string &windowName, dimension2d <u32> size, const bool &fullscreen) : debug(
        false) {
    const wstring title(windowName.begin(), windowName.end());

    device = createDevice(video::EDT_OPENGL, size, 16, fullscreen, false, false, &receiver);
    if (!device)
        throw ERROR("Device can't be created");
    device->setWindowCaption(title.c_str());
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNodeFPS(0, 100, 0.05);
    device->getCursorControl()->setVisible(false);
}

Window::~Window() {
    close();
    device->drop();
}

/*
 * Getters // Setters
 */
const bool &Window::getDebugMode() const {
    return debug;
}

void Window::setDebugMode(const bool &active) {
    debug = active;
}

ISceneManager *Window::getSmgr() {
    return smgr;
}

/*
 * Methods
 */
/**
 * Use to close the window
 */
void Window::close() {
    device->closeDevice();
}

/**
 * Check if the window is open
 * @return Window status
 */
bool Window::isOpen() {
    return device->run();
}

/**
 * Display the window
 */
void Window::display() {
    if (debug)
        debugMode();
    driver->beginScene();
    smgr->drawAll();
    guienv->drawAll();
    driver->endScene();
}

/**
 * Get the mesh given in parameter
 * @param fileName
 * @return Mesh
 */
IAnimatedMesh *Window::getModel(const std::string &fileName) {
    return smgr->getMesh(fileName.c_str());
}

/**
 * Get the texture given in parameter
 * @param fileName
 * @return Texture
 */
ITexture *Window::getTexture(const std::string &fileName) {
    return driver->getTexture(fileName.c_str());
}

/**
 * Add a cube to the SceneNode
 * @param texture
 * @return Scene if success, nullptr otherwise
 */
ISceneNode *Window::addCube(const std::string &texture) {
    scene::ISceneNode *node = smgr->addCubeSceneNode(1);

    if (!node)
        return nullptr;
    node->setMaterialTexture(0, driver->getTexture(texture.c_str())); // ? throw if getTexture failed
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    return node;
}

/**
 * Add a mesh to the AnimatedMesh
 * @param model
 * @param texture
 * @return AnimatedMeshSceneNode node if success, nullptr otherwise
 */
IAnimatedMeshSceneNode *Window::addAnimatedMesh(const std::string &model, const std::string &texture) {
    IAnimatedMesh *mesh = smgr->getMesh(model.c_str());
    IAnimatedMeshSceneNode *node;

    if (!mesh)
        return nullptr;
    node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture(texture.c_str()));

        const core::aabbox3d <f32> boundingBox = node->getTransformedBoundingBox();
        const vector3df size = boundingBox.getExtent();
        float scale = 1 / size.X;

        if (1 / size.Y < scale)
            scale = 1 / size.Y;
        if (1 / size.Z < scale)
            scale = 1 / size.Z;
        node->setScale(vector3df(scale, scale, scale));
    }
    return node;
}

/**
 * Move the Scene nod to initPos to destPos
 * @param initPos
 * @param destPos
 * @param timestamp
 * @return Animation created (FlyStraightAnimator)
 */
ISceneNodeAnimator *Window::createTranslation(const vector3df &initPos, const vector3df &destPos, const u32 &timestamp) {
    return smgr->createFlyStraightAnimator(initPos, destPos, timestamp);
}

/**
 * Add a camera to the window
 * @param pointOfView
 * @param lookAt
 * @return Camera created
 */
ICameraSceneNode *Window::getCameraSceneNode(const vector3df &pointOfView, const vector3df &lookAt) {
    return smgr->addCameraSceneNode(0, pointOfView, lookAt);
}

/**
 * Getter on the keyboard
 * @param keyCode
 * @return Key pressed
 */
bool Window::isKeyPressed(const irr::EKEY_CODE &keyCode) const {
    return receiver.IsKeyDown(keyCode);
}

/**
 * Change window background
 * @param Background path
 */
void Window::changeSkybox(const std::string &fileName) {
    smgr->addSkyDomeSceneNode(getTexture(fileName));
}

/**
 * Move the camera
 * \see CameraMove.cpp
 * @param CameraMove
 * @return Animation create with the move given in parameter
 */
ISceneNodeAnimator *Window::applyCameraMove(const CameraMove &cameraMove) {
    scene::ICameraSceneNode *camera = nullptr;
    scene::ISceneNodeAnimator *sa = nullptr;

    camera = getCameraSceneNode(cameraMove.getPoints()[0], cameraMove.getTargetPos());
    sa = smgr->createFollowSplineAnimator(device->getTimer()->getTime(), cameraMove.getPoints(),
                                          cameraMove.getSpeed(), cameraMove.getTightness(),
                                          cameraMove.getLoop());
    camera->addAnimator(sa);
    sa->drop();
    return sa;
}

/**
 * Display the current number of FPS
 */
void Window::debugMode() {
    wchar_t text[255];
    IGUISkin *skin;

    guienv->clear();
    swprintf(text, 255, L"FPS: %3d", driver->getFPS()); // ?
    skin = guienv->getSkin();
    skin->setColor(gui::EGDC_BUTTON_TEXT, video::SColor(255, 255, 255, 0));
    guienv->addStaticText(text, rect<s32>(10, 10, 55, 22), true);
}

/**
 * Allow or not the resized mode
 * @param isResize
 */
void Window::canBeResized(bool isResize) {
    device->setResizable(isResize);
}