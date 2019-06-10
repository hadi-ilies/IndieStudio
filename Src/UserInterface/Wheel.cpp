/*
** EPITECH PROJECT, 2019
** wheel
** File description:
** Wheel
*/

#include "UserInterface/Wheel.hpp"

/*
 * Constructors // Destructors
 */
Wheel::Wheel(const vector3df &position, const float &radius, const std::vector<std::string> &buttonsNames) : MenuElement(position, "Wheel"),
                                                                                                             radius(radius),
                                                                                                             currentButton(0) {
    for (uint i = 0 ; i < buttonsNames.size() ; i++) {
        vector3df pos = getPosButton(i);
        buttonList.push_back(new FontButton(pos, buttonsNames[i]));
    }
}

Wheel::Wheel(const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons) : MenuElement(position,
                                                                                                                           "Wheel"),
                                                                                                               radius(radius),
                                                                                                               currentButton(0) {
    //std::cout << "Position :" << position.X << "  " << position.Y << "  " << position.Z << std::endl;
    for (uint i = 0 ; i < buttons.size() ; i++) {
        vector3df pos = getPosButton(i);
        //  std::cout << "WIWI" << std::endl;
        buttonList.push_back(new Button(pos, buttons[i].name, buttons[i].model, buttons[i].texture));
    }
}

Wheel::~Wheel() = default;

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
        for (uint i = 0 ; i < buttonList.size() ; i++)
            buttonList[i]->animation(getPosButton((i + currentButton + buttonList.size() + direction) % buttonList.size()), timestamps);
        currentButton = (currentButton + buttonList.size() + direction) % buttonList.size();
    }
}