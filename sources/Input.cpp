//
// Created by vladi on 4/14/2022.
//

#include "../headers/Input.hpp"

#include <utility>

Input::Input(std::string label, sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor): label(std::move(label)){
    rect.setSize(size);
    rect.setPosition(pos);
    rect.setFillColor(fillColor);
    rect.setOutlineColor(outlineColor);
    rect.setOutlineThickness(3.f);

    font.loadFromFile("resources/arial.ttf");
    characterSize = (unsigned int)size.y / 2;

}

bool Input::checkInsideBox(sf::Vector2i mousePos) {
    sf::Vector2f topLeft = rect.getPosition();
    sf::Vector2f bottomRight = topLeft + rect.getSize();
    return
            (float)mousePos.x >= topLeft.x && (float)mousePos.x <= bottomRight.x &&
            topLeft.y <= (float)mousePos.y && (float)mousePos.y <= bottomRight.y;
}

sf::Color Input::setOpacity(sf::Color color, unsigned int alpha){
    color.a = (sf::Uint8)alpha;
    return color;
}

std::string Input::getLabel() {
    return label;
}
