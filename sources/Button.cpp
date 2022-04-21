//
// Created by vladi on 4/14/2022.
//

#include "../headers/Button.hpp"

#include <utility>

Button::Button(std::string label, std::string _action, sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor):
        Input(std::move(label), pos, size, fillColor, outlineColor), rectHovered(rect), action(std::move(_action)) {
    isHovered = false;
    rectHovered.setFillColor(setOpacity(rect.getFillColor(), 128));
    rectHovered.setOutlineColor(setOpacity(rect.getOutlineColor(), 128));
}

bool Button::listen(sf::Event event, sf::Vector2i mousePos){
    isHovered = checkInsideBox(mousePos);
    return isHovered && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
}

std::string Button::getAction(){
    return action;
}

sf::Text Button::getTextRect() const{
    sf::Text text(label, font, characterSize);
    sf::RectangleShape newRect({text.getLocalBounds().getSize()});

    sf::Vector2f newSize = newRect.getSize();
    sf::Vector2f newPos;
    sf::Vector2f oldPos = rect.getPosition();
    sf::Vector2f oldSize = rect.getSize();

    newPos.x = oldPos.x + oldSize.x / 2 - newSize.x / 2;
    newPos.y = oldPos.y + oldSize.y / 2 - newSize.y * 0.8f;

    text.setPosition(newPos);
    text.setFillColor(sf::Color::Black);

    return text;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates) const{
    if(isHovered)
        target.draw(rectHovered);
    else
        target.draw(rect);
    target.draw(getTextRect());
}

Input* Button::clone() const {
    return new Button (*this);
}