/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Menu
*/

#include "JukeBox.hpp"
#include "UserInterface/Menu.hpp"

/*
 *   Constructors // Destructors
 */
Menu::Menu(Window &_window, IrrFontBuffer &_irrFontBuffer, std::string _name, const vector3df &cameraPos, const vector3df &targetPos)
    : window(_window),
      irrFontBuffer(_irrFontBuffer),
      name(std::move(_name)),
      prevMenu(nullptr),
      position(cameraPos),
      targetPosition(targetPos)
{
}

Menu::~Menu() {
    for (auto &it : MenuElements)
        delete it;
}

/*
 *   Getters // Setters
 */
const std::string Menu::getName() const {
    return name;
}

Menu *Menu::getMenuFromName(const std::string &_name)
{
    if (linkMap.find(name) != linkMap.end())
        return linkMap.at(_name);
    return nullptr;
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
    return static_cast<Wheel*>(MenuElements.back())->getCurrentButton()->getName();
}

std::string Menu::getCurrentButtonTexture() const {
    return dynamic_cast<Button*> (static_cast<Wheel*>(MenuElements.back())->getCurrentButton())->getTexture();
}

std::string Menu::getCurrentButtonModel() const {
    return dynamic_cast<Button*> (static_cast<Wheel*>(MenuElements.back())->getCurrentButton())->getModel();
}

bool Menu::getKey() {
    if (window.isKeyPressed(KEY_SPACE) || window.isKeyPressed(KEY_RETURN)) {
        JukeBox::getInstance().playSound("Enter");
        return true;
    }
    if (window.isKeyPressed(KEY_RIGHT)) {
        static_cast<Wheel*>(MenuElements.back())->turnButtons(Wheel::RIGHT, 100);
    } else if (window.isKeyPressed(KEY_LEFT)) {
        static_cast<Wheel*>(MenuElements.back())->turnButtons(Wheel::LEFT, 100);

    }
    return false;
}

void Menu::linkMenu(const std::string &_name, Menu *menu) {
    linkMap[_name] = menu;
}

void Menu::addWheel(const vector3df &_position, const float &radius, const std::vector<std::string> &buttonsNames)
{
    MenuElements.push_back(new Wheel(window, _position, radius, buttonsNames, irrFontBuffer));
}

void Menu::addWheel(const vector3df &_position, const float &radius, const std::vector<Wheel::ParamButton> &buttons) {
    MenuElements.push_back(new Wheel(window, _position, radius, buttons));
}

void Menu::addButton(const vector3df &_position, const std::string &_name, const std::string &model, const std::string &texture) {
    //MenuElements.push_back(new ButtonElement(_position, _name, model, texture));
}
