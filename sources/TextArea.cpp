//
// Created by vladi on 4/14/2022.
//

#include "../headers/TextArea.hpp"

#include <utility>

TextArea::TextArea(std::string label, sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor):
        Input(std::move(label), pos, size, fillColor, outlineColor){
    isSelected = false;
    maxLength = (unsigned int)rect.getSize().x * 3 / characterSize / 2;
    rectSelected = rect;
    rectSelected.setOutlineColor(setOpacity(rect.getOutlineColor(), 128));
    rectSelected.setOutlineThickness(6);
}

void TextArea::setValue(std::string newValue) {
    value = std::move(newValue);
}

std::string TextArea::getValue() const {
    return value;
}

void TextArea::insertChar(char ch) {
    value.push_back(ch);
}

void TextArea::deleteChar() {
    if(value.length() == 0)
        return;
    value.pop_back();
}

bool TextArea::checkValidChar(unsigned int unicode) {
    return (unicode >= 65 && unicode <= 90) || (unicode >= 48 && unicode <= 57) || (unicode >= 97 && unicode <= 122)
           || unicode == 32 || unicode == 95 || unicode == 47 || unicode == 59 || unicode == 45;
}

bool TextArea::listen(sf::Event event, sf::Vector2i mousePos) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        isSelected = checkInsideBox(mousePos);
    else if(isSelected && event.type == sf::Event::TextEntered && checkValidChar(event.text.unicode))
        insertChar(static_cast<char>(event.text.unicode));
    else if(isSelected && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace)
        deleteChar();
    return false;
}

sf::Text TextArea::getTextRect() const{
    std::string s;
    if(value.length() == 0)
        s = label.length() > maxLength ? label.substr(label.length() - maxLength) : label;
    else{
        s = value.length() > maxLength ? value.substr(value.length() - maxLength) : value;
        if(label == "Password")
            s = std::string(s.length(), '#');
    }
    sf::Text text(s, font, characterSize);
    sf::RectangleShape newRect({text.getLocalBounds().getSize()});

    sf::Vector2f newSize = newRect.getSize();
    sf::Vector2f newPos;
    sf::Vector2f oldPos = rect.getPosition();
    sf::Vector2f oldSize = rect.getSize();

    newPos.x = oldPos.x;
    newPos.y = oldPos.y + oldSize.y / 2 - newSize.y * 0.8f;

    text.setPosition(newPos);
    text.setFillColor(sf::Color::Black);

    return text;
}

void TextArea::draw(sf::RenderTarget& target, sf::RenderStates) const{
    if(isSelected)
        target.draw(rectSelected);
    else
        target.draw(rect);
    target.draw(getTextRect());
}

Input* TextArea::clone() const {
    return new TextArea(*this);
}