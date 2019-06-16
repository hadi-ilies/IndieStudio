/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Wheel
*/

#include "UserInterface/Wheel.hpp"

/*
 * Constructors // Destructors
 */
Wheel::Wheel(Window &_window, const vector3df &position, const float &radius, const std::vector<std::string> &buttonsNames, IrrFontBuffer &irrFontBuffer)
    : MenuElement(position, "Wheel"),
      radius(radius),
      currentButton(0),
      displayedButton(0)
{
    for (uint i = 0 ; i < buttonsNames.size() ; i++) {
        vector3df pos = getPosButton(i);
        buttonList.push_back(new FontButton(_window, pos, buttonsNames[i], irrFontBuffer));
    }
    turnButtons(BASE, 1000);
}

Wheel::Wheel(Window &_window, const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons)
    : MenuElement(position, "Wheel"),
      radius(radius),
      currentButton(0)
{
    for (uint i = 0 ; i < buttons.size() ; i++) {
        vector3df pos = getPosButton(i);
        buttonList.push_back(new Button(_window, pos, buttons[i].name, buttons[i].model, buttons[i].texture));
    }
    turnButtons(BASE, 1000);
}

Wheel::~Wheel() {
    for (auto &it : buttonList)
        delete it;
}

/*
 * Getters // Setters
 */
AButton *Wheel::getButton(const uint &buttonIndex) const {
    return buttonList[buttonIndex];
}

AButton *Wheel::getCurrentButton() const {
    return buttonList[currentButton];
}

/*
 * Methods
 */
const vector3df Wheel::getPosButton(const uint &buttonIndex) {
    return vector3df(radius * cos(2 * buttonIndex * M_PI / buttonList.size()) + position.X, position.Y,
                     radius * sin(2 * buttonIndex * M_PI / buttonList.size() + position.Z));
}

void Wheel::turnButtons(const Wheel::Dir &direction, const f32 &timestamps) {
    if (buttonList[0]->isAnimationFinished()) {
        for (uint i = 0 ; i < buttonList.size(); i++)
            buttonList[i]->animation(getPosButton((i + displayedButton + buttonList.size() + direction) % buttonList.size()), timestamps);
        displayedButton = (displayedButton + buttonList.size() + direction) % buttonList.size();
        currentButton = displayedButton == 0 ? 0 : (buttonList.size() - displayedButton);
        JukeBox::getInstance().playSound("Switch");
    }
}
