#include <utility>

/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#include "JukeBox.hpp"
#include "UserInterface/Menu.hpp"

/*
 *   Constructors // Destructors
 */
Menu::Menu(std::string  name, const vector3df &cameraPos, const vector3df &targetPos) : name(std::move(name)), prevMenu(nullptr),
                                                                                             position(cameraPos),
                                                                                             targetPosition(targetPos) {
}

Menu::~Menu() = default;

/*
 *   Getters // Setters
 */
const std::string Menu::getName() const {
    return name;
}


const vector3df &Menu::getPosition() const {
    return position;
}

const vector3df &Menu::getTargetPosition() const {
    return targetPosition;
}

Menu *Menu::getPrevMenu() const {
    return prevMenu;
}

void Menu::setPrevMenu(Menu *menu) {
    prevMenu = menu;
}
/*
 *   Methods
 */
Menu *Menu::getMenu() {
    if (linkMap.find(getCurrentButtonName()) != linkMap.end())
        return linkMap[getCurrentButtonName()];
    return nullptr;
}

std::string Menu::getCurrentButtonName() const {
    return static_cast<Wheel *>(MenuElements.back())->getCurrentButton()->getName();
}

std::string Menu::getCurrentButtonTexture() const {
    return dynamic_cast<Button *> (static_cast<Wheel *>(MenuElements.back())->getCurrentButton())->getTexture();
}

std::string Menu::getCurrentButtonModel() const {
    return dynamic_cast<Button *> (static_cast<Wheel *>(MenuElements.back())->getCurrentButton())->getModel();
}

bool Menu::getKey() {
    //std::cout << getCurrentButtonName() << std::endl;
    if (Window::getInstance().isKeyPressed(KEY_SPACE) || Window::getInstance().isKeyPressed(KEY_RETURN)) {
        JukeBox::getInstance().playSound("Enter");
        return true;
    }
    if (Window::getInstance().isKeyPressed(KEY_RIGHT)) {
        static_cast<Wheel *>(MenuElements.back())->turnButtons(Wheel::RIGHT, 1000);
        JukeBox::getInstance().playSound("Switch");
    } else if (Window::getInstance().isKeyPressed(KEY_LEFT)) {
        static_cast<Wheel *>(MenuElements.back())->turnButtons(Wheel::LEFT, 1000);
        JukeBox::getInstance().playSound("Switch");
    }
    return false;
}

bool Menu::linkMenu(const std::string &_name, Menu *menu) {
    linkMap[_name] = menu;
}

bool Menu::addWheel(const vector3df &_position, const float &radius, const std::vector<std::string> &buttonsNames) {
    MenuElements.push_back(new Wheel(_position, radius, buttonsNames));
}

bool Menu::addWheel(const vector3df &_position, const float &radius, const std::vector<Wheel::ParamButton> &buttons) {
    MenuElements.push_back(new Wheel(_position, radius, buttons));
}

bool Menu::addButton(const vector3df &_position, const std::string &_name, const std::string &model, const std::string &texture) {
    //MenuElements.push_back(new ButtonElement(_position, _name, model, texture));
}
