/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** EventReceiver.hpp
*/

#ifndef EVENTRECEIVER_HPP
#define EVENTRECEIVER_HPP

#include <irrlicht/irrlicht.h>

using namespace irr;

class EventReceiver : public IEventReceiver
{
public:
    EventReceiver() {
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }
    bool OnEvent(const irr::SEvent &event) {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }
    bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif
