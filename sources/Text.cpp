//
// Created by vladi on 4/15/2022.
//

#include "../headers/Text.hpp"

#include <utility>

Text::Text(std::string label, sf::Vector2f pos, sf::Vector2f size, sf::Color fillColor,sf::Color outlineColor):Input{
        std::move(label), pos, size, fillColor, outlineColor}{}


void Text::setTextRect() {
    textRect = getTextRect();
}

sf::Text Text::getTextRect() const{
    sf::Text text(label, font, characterSize);
    text.setPosition(rect.getPosition());
    text.setFillColor(sf::Color::Black);
    return text;
}

sf::Vector2f Text::getSize() const{
    return textRect.getLocalBounds().getSize();
}

bool Text::listen(sf::Event, sf::Vector2i) {
    return false;
}

void Text::draw(sf::RenderTarget &target, sf::RenderStates) const {
    target.draw(textRect);
}

Input* Text::clone() const {
    return new Text(*this);
}