/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Window.hpp
*/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <irrlicht/irrlicht.h>

using namespace std;
using namespace irr;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*class EventReceiver : public IEventReceiver
{
public:
    virtual bool OnEvent(const SEvent &event) // ? virtual
        {
            // Remember whether each key is down or up
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

            return false;
        }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const // ? virtual
        {
            return KeyIsDown[keyCode];
        }

    MyEventReceiver()
        {
            for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                KeyIsDown[i] = false;
        }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    };*/

class Window
{
public:
    Window(const string &windowName, const dimension2d<u32> &size, const bool &fullscreen);
    ~Window();
    bool isOpen();
    IAnimatedMeshSceneNode *addAnimatedMesh(const string &model, const string &texture);

private:
    EventReceiver receiver;
    IrrlichtDevice *device;
    IVideoDriver *driver;
    ISceneManager *smgr;
    IGUIEnvironment *guienv;
};

#endif
